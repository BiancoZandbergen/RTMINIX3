/* The kernel call implemented in this file:
 *   m_type:    SYS_RT_SET_SCHED
 *
 * The parameters for this kernel call are:
 *    m7_i2:    RT_SCHED    Scheduler type
 */

#include "../system.h"
#include <minix/type.h>
#include <sys/resource.h>
#include <minix/rt.h>


/*===========================================================================*
 *                  do_rt_set_sched                       				     *
 *===========================================================================*/
PUBLIC int do_rt_set_sched(message *m_ptr)
{
  /* Set the real-time scheduler.
   * Currently supported schedulers are
   * Rate-Monotonic (SCHED_RM) and
   * Earliest Deadline First (SCHED_EDF).
   */

  /* Check if allowed to change the RT scheduler. 
   * It is only allowed to change the scheduler if
   * rt_sched is SCHED_UNDEFINED or rt_sched is set
   * to a scheduler but there are no real-time processes
   * running.
   */
  if (rt_sched != SCHED_UNDEFINED) {
      register struct proc * xp;  
    
      /* search the process table for RT processes */
      for (xp = BEG_PROC_ADDR; xp < END_PROC_ADDR; ++xp) {
          if (is_rtp(xp)) {
              return (EPERM); /* found RT process */
          }
      }
  } 

  /* We are allowed to set the scheduler.
   * Check if the scheduler type is valid
   * and set rt_sched to the new scheduler type
   */
  switch (m_ptr->RT_SCHED) {
      case SCHED_UNDEFINED:
          rt_sched = m_ptr->RT_SCHED;
          break;
      case SCHED_RM:
          if (m_ptr->RM_PRIO_POLICY != PRIO_UNIQUE &&
              m_ptr->RM_PRIO_POLICY != PRIO_NOT_UNIQUE) {
              return (EINVAL); /* invalid policy parameter */
          }
          
          rt_sched = m_ptr->RT_SCHED;
          rm_prio_policy = m_ptr->RM_PRIO_POLICY;
      case SCHED_EDF:
          rt_sched = m_ptr->RT_SCHED;
          break;
      default:
          return (EINVAL); /* invalid scheduler */
          break;
  }        
      
  return (OK);    
}

