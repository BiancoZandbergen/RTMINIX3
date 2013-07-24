/* The system library function implemented in this file:
 *   sys_rt_sched_bridge
 *
 * Function description:
 *   This function does the kernel call to set the scheduler
 *   bridge state. Depending on this state system processes
 *   are allowed or not allowed to get a lower priority than
 *   RT processes.
 * 
 * The parameters for this library function are:
 *   state:     scheduling bridge state
 *
 * Return value:
 *   Returns 0 if the operation succeeded.
 *   If the return value is not 0 the error code
 *   is returned.
 */
#include "syslib.h"
#include <minix/rt.h>

int sys_rt_sched_bridge(int state)
{
  message m; /* message we use for the kernel call */
  
  m.RT_SCHED_BRIDGE = state; /* set the bridge state */
  
  /* do the kernel call and return the result */
  return (_taskcall(SYSTASK, SYS_RT_SCHED_BRIDGE, &m));
}    

