/* The kernel call implemented in this file:
 *   m_type:    SYS_RT_SET
 *
 * The parameters for this kernel call are:
 *    m7_i1     RT_ENDPT        endpoint of process that wants to be RT
 *    m7_i2     RT_SCHED        Scheduler type
 *    m7_i3     RM_PRIO         rate-monotonic static priority (used by RM only)
 *    m7_i3     EDF_PERIOD      period of process (used by EDF only)
 *    m7_i4     EDF_CALCTIME    calculation time per period (used by EDF only)
 */

#include "../system.h"
#include <minix/type.h>
#include <sys/resource.h>
#include <minix/rt.h>

FORWARD _PROTOTYPE( int do_rt_set_rm, (message *m_ptr, struct proc *rp) );
FORWARD _PROTOTYPE( int do_rt_set_edf, (message *m_ptr, struct proc *rp) );

/*===========================================================================*
 *                  do_rt_set                                                *
 *===========================================================================*/
PUBLIC int do_rt_set(message *m_ptr)
{
  /* Transform a normal user process into a real-time process */
    
  struct proc *rp; /* pointer to process that wants to be real-time */
  int proc_nr; /* process number of process that wants to be real-time */
  
  /* if scheduler is undefined we cannot
   * make processes real-time
   */    
  if (rt_sched == SCHED_UNDEFINED) {
      return (EPERM);
  }

  /* if rt_sched is not equal to the
   * scheduler defined in the message
   * we cannot make this process real-time
   */
  if (rt_sched != m_ptr->RT_SCHED) {
      return (EINVAL);
  }  
  
  /* check if endpoint is valid and convert endpoint
   * to process number stored in proc_nr
   */
  if (! isokendpt(m_ptr->RT_ENDPT, &proc_nr)) {
      return (EINVAL);
  }

  /* get pointer to process from process number */
  rp = proc_addr(proc_nr);
  
  /* a process that is already real-time may
   * not call this function.
   */
  if (is_rtp(rp)) {
      return (EPERM);
  }    
  
  /* Dispatch to the right function.
   * Each scheduler type has its own function.
   */
  switch (rt_sched) {
      case SCHED_RM:
          return do_rt_set_rm(m_ptr, rp);
      case SCHED_EDF:
          return do_rt_set_edf(m_ptr, rp);
      default:
          return (EINVAL);
  }        
    
  /* should not be reached */  
  return (EPERM);    
}


/*===========================================================================*
 *                  do_rt_set_rm                                             *
 *===========================================================================*/
PRIVATE int do_rt_set_rm(message *m_ptr, struct proc *rp)
{
  struct proc *xp;    
    
  /* if rm_prio_policy equals PRIO_UNIQUE the priority of a
   * process scheduled with RM should be unique. We will have to
   * loop through the process table to check if there is no other process
   * with this priority.
   */
  if (rm_prio_policy == PRIO_UNIQUE) {
      for (xp = BEG_PROC_ADDR; xp < END_PROC_ADDR; ++xp) {
          if (xp->p_rts_flags != SLOT_FREE && 
              is_rtp(xp) && xp->p_rt_priority == m_ptr->RM_PRIO) {
              return (EINVAL);
          }    
      }
  }    
 
  if ( rp->p_rts_flags == 0) {
      /* Should not happen normally.
       * A process is runnable if p_rts_flags is zero.
       * The process requesting to be real-time should be
       * blocked waiting for a reply from PM 
       * and thus p_rts_flags should not be zero.
       * Still we remove the process from the scheduling queue.
       */
       lock_dequeue(rp);
  }

  /* Now we can change the process structure.
   * First make sure this process will be recognized
   * as a real-time process.
   */
   rp->p_rt = 1;
      
  /* Set the current and maximum priority to the
   * real-time queue.
   */
  rp->p_max_priority = rp->p_priority = RT_Q;

  /* set the static priority */
  rp->p_rt_priority = m_ptr->RM_PRIO;

  if ( rp->p_rts_flags == 0) {
      /* Should not happen normally.
       * See above. Add process to the scheduling queue.
       */
      lock_enqueue(rp);
  }

  return (OK);
}    

/*===========================================================================*
 *                  do_rt_set_edf                                            *
 *===========================================================================*/
PRIVATE int do_rt_set_edf(message *m_ptr, struct proc * rp)
{
  /* check if period and calculation time
   * parameters are valid
   */
  if (m_ptr->EDF_PERIOD <= 0 || m_ptr->EDF_CALCTIME <= 0) {
      return (EINVAL);
  }

  /* check if calctime is not larger than period */
  if (m_ptr->EDF_CALCTIME > m_ptr->EDF_PERIOD) {
      return (EINVAL);
  }    
    
  if ( rp->p_rts_flags == 0) {
      /* Should not happen normally.
       * A process is runnable if p_rts_flags is zero.
       * The process requesting to be real-time should be
       * blocked waiting for a reply from PM 
       * and thus p_rts_flags should not be zero.
       * In the case of EDF this is fatal.
       */
       kprintf("systask: do_rt_set (edf): process should not be runnable\n");
       return (EGENERIC);
  }
  
  /* Now we can change the process structure.
   * First make sure this process will be recognized
   * as a real-time process.
   */
   rp->p_rt = 1;

   /* set the period and calculation time */
   rp->p_rt_period = m_ptr->EDF_PERIOD;
   rp->p_rt_calctime = m_ptr->EDF_CALCTIME;

   /* The first period starts immediately,
    * so set the number of ticks left in this period
    * to the requested calculation time.
    */
   rp->p_rt_ticksleft = rp->p_rt_calctime;

   /* ticks left till next period equals the specified period */
   rp->p_rt_nextperiod = rp->p_rt_period;

   /* use the EDF scheduling queue */
   rp->p_priority = rp->p_max_priority = RT_Q;

   /* The process should be blocked waiting for a reply
    * from PM. So we add the process to the (front of) block list. 
    */
   rp->p_rt_link = edf_block_head;
   edf_block_head = rp;

   /* we did not modify edf_rp or the edf run queue so we don't have
    * to call edf_sched()
    */

   return (OK);
}   

