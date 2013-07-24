/* The system library function implemented in this file:
 *   sys_rt_set_sched
 *
 * Function description:
 *   This function sets the real-time scheduler.
 * 
 * The parameters for this library function are:
 *   type:      scheduler type
 *   policy:    Rate-Monotonic priority policy (used by RM only)
 *
 * Return value:
 *   Returns 0 if the operation succeeded.
 *   If the return value is not 0 the error code
 *   is returned.
 */
#include "syslib.h"
#include <minix/rt.h>

int sys_rt_set_sched(int type, int policy)
{
  message m; /* message we use for the kernel call */

  m.RT_SCHED = type; /* set the scheduler type */
    
  /* rate-monotonic specific parameter */
  if (type == SCHED_RM) {
      m.RM_PRIO_POLICY = policy; /* set the prio policy */
  }    
  
  /* do the kernel call and return the result */
  return (_taskcall(SYSTASK, SYS_RT_SET_SCHED, &m));
}    

