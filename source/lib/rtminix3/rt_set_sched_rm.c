/* The library function implemented in this file:
 *   rt_set_sched_rm
 *
 * Function description:
 *   This function sets the real-time scheduler to Rate-Monotonic.
 * 
 * The parameters for this library function are:
 *   int prio_policy        the priority of a RM process can be
 *                          enforced to be unique (PRIO_UNIQUE) or
 *                          not (PRIO_NOT_UNIQUE)
 *
 * Return value:
 *   Returns 0 if the operation succeeded.
 *   If the return value is not 0 the error code
 *   is saved in errno.
 */
#include <lib.h>
#include <minix/rt.h>

int rt_set_sched_rm(int prio_policy)
{
  message m; /* message we use for the system call */
  
  m.RT_SCHED = SCHED_RM; /* set the scheduler parameter to RM */
  m.RM_PRIO_POLICY = prio_policy; /* set the priority policy parameter */

  /* do the system call and return the result */
  return (_syscall(MM, RT_SET_SCHED, &m));
}   

