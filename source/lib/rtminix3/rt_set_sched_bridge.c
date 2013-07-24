/* The library function implemented in this file:
 *   rt_set_sched_bridge
 *
 * Function description:
 *   Set the rt_sched_bridge value in the kernel.
 *   Depending on this value a system process may or may not
 *   have a lower priority than real-time processes. A system process
 *   can be lowered in priority due to using its full quantum.
 *   This function is in general only used when shutting down.
 *   At shutdown system processes must be able to get a lower priority than
 *   RT processes otherwise the system won't shutdown properly and crashes.
 * 
 * The parameters for this library function are:
 *   int state              The state of the scheduling bridge.
 *                          if 0 system process cannot have a lower priority
 *                          than RT processes. if 1 a system process can.
 *
 * Return value:
 *   Returns 0 if the operation succeeded.
 *   If the return value is not 0 the error code
 *   is saved in errno.
 */
#include <lib.h>
#include <minix/rt.h>

int rt_set_sched_bridge(int state)
{
  message m; /* message we use for the system call */
    
  m.RT_SCHED_BRIDGE = state; /* set the state */

  /* do the system call and return the result */
  return (_syscall(MM, RT_SET_SCHED_BRIDGE, &m));
}    

