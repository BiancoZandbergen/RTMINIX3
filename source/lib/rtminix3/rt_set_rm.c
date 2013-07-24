/* The library function implemented in this file:
 *   rt_set_rm
 *
 * Function description:
 *   This function transforms a normal user process into a
 *   real-time process scheduled using Rate-Monotonic.
 *   The operation will only succeed if the RT scheduler is already
 *   set to RM using the rt_set_sched_rm() library call.
 * 
 * The parameters for this library function are:
 *   int period        The fixed priority of the RM process
 *                     compared to other RM processes.
 *                     This can be any positive or negative number.
 *                     If the priority policy is PRIO_UNIQUE,
 *                     this priority may not be in use by an other
 *                     RM process.
 *
 * Return value:
 *   Returns 0 if the operation succeeded.
 *   If the return value is not 0 the error code
 *   is saved in errno.
 */
#include <lib.h>
#include <minix/rt.h>

int rt_set_rm(int prio)
{
  message m; /* message we use for the system call */

  m.RT_SCHED = SCHED_RM; /* set the scheduler type */
  m.RM_PRIO = prio; /* set the Rate-Monotonic priority */

  /* do the system call and return the result */
  return (_syscall(MM, RT_SET, &m));
}    

