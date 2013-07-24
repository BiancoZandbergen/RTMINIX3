/* The library function implemented in this file:
 *   rt_set_edf
 *
 * Function description:
 *   This function transforms a normal user process into a
 *   real-time process scheduled using Earliest Deadline First.
 *   The operation will only succeed if the RT scheduler is already
 *   set to EDF using the rt_set_sched_edf() library call.
 * 
 * The parameters for this library function are:
 *   int period        The period of the process in ticks
 *   int calctime      The reserved calculation time within
 *                     each period in ticks
 *
 * Return value:
 *   Returns 0 if the operation succeeded.
 *   If the return value is not 0 the error code
 *   is saved in errno.
 */
#include <lib.h>
#include <minix/rt.h>

int rt_set_edf(int period, int calctime)
{
  message m; /* message we use for system call */

  m.RT_SCHED = SCHED_EDF; /* set scheduler type */
  m.EDF_PERIOD = period; /* set period in ticks */
  m.EDF_CALCTIME = calctime; /* set calculation time within each period in ticks */

  /* do the system call and return the result */
  return (_syscall(MM, RT_SET, &m));
}    

