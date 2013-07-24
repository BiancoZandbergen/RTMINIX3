/* The kernel call implemented in this file:
 *   m_type:    SYS_RT_NEXTPERIOD
 *
 * The parameters for this kernel call are:
 *    m7_i1:    RT_ENDPT  Endpoint of process that wants to give up calc time
 */

#include "../system.h"
#include <minix/type.h>
#include <sys/resource.h>
#include <minix/rt.h>


/*===========================================================================*
 *                  do_rt_nextperiod                                         *
 *===========================================================================*/
PUBLIC int do_rt_nextperiod(message *m_ptr)
{
  /* A process scheduled using Earliest Deadline First can give up
   * remaining calculation time using this kernel call.
   * A process that invoked this kernel call is on the block list waiting
   * for a reply from PM. We will have to remove it from the block list
   * and put it on the wait queue waiting for the next period.
   */
  struct proc * rp;
  struct proc **xpp;
  int proc_nr;

  /* if rt_sched is not SCHED_EDF this kernel call
   * is not allowed!
   */
  if (rt_sched != SCHED_EDF) {
      return (EPERM);
  }    
  
  /* check if endpoint is valid and convert endpoint to
   *  process number stored in proc_nr
   */
  if (! isokendpt(m_ptr->RT_ENDPT, &proc_nr)) {
      return (EINVAL);
  }        
  
  /* get pointer to process from proc_nr */
  rp = proc_addr(proc_nr);

  /* check if process is real-time */
  if (! is_rtp(rp) ) {
      return (EPERM);
  }    
  
  if (rp->p_rts_flags == 0) {
      /* p_rts_flags cannot be 0 because
       * the process is waiting for a reply from
       * PM
       */
      return (EPERM);
  }    
  
  /* remove process from the block list.
   * We first have to find the process in the list.
   */
  xpp = &edf_block_head;
  while (*xpp != NIL_PROC && *xpp != rp) {
      xpp = &(*xpp)->p_rt_link;
  }

  /* *xpp == NIL_PROC if the list was empty or process not found.
   * This may not happen normally.
   */
  if (*xpp != NIL_PROC) {
      /* Remove the process from the list.
       * We set the pointer that points to the process we remove
       * to the process that the process we remove is linked to.
       */
      *xpp = (*xpp)->p_rt_link;
  }  

  /* Add process to the wait queue.
   * This quueue is sorted on next period start.
   * We will have to find the right place in the queue first.
   */
  xpp = &edf_wait_head;
  while (*xpp != NIL_PROC && (*xpp)->p_rt_nextperiod <= rp->p_rt_nextperiod) {
      xpp = &(*xpp)->p_rt_link;
  }

  /* Add process to the queue */
  rp->p_rt_link = *xpp;
  *xpp = rp;  
  
  /* Make sure that no other code will schedule this process
   * until the new period starts by setting the NEXTPERIOD bit.
   * If p_rts_flags is not 0, a process is not runnable.
   */
  rp->p_rts_flags |= NEXTPERIOD;
 
  #if 0
  kprintf("%d %s gave up %d/%d ticks\n", rp->p_endpoint, rp->p_name, rp->p_rt_ticksleft, rp->p_rt_calctime);
  #endif
  
  return (OK);    
}

