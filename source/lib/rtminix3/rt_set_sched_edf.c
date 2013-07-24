/* The library function implemented in this file:
 *   rt_set_sched_edf
 *
 * Function description:
 *   This function sets the real-time scheduler to Earliest Deadline First.
 * 
 * The parameters for this library function are:
 *   none
 *
 * Return value:
 *   Returns 0 if the operation succeeded.
 *   If the return value is not 0 the error code
 *   is saved in errno.
 */
#include <lib.h>
#include <minix/rt.h>

int rt_set_sched_edf(void)
{
  message m; /* message we use for the system call */
    
  m.RT_SCHED = SCHED_EDF; /* Set the scheduler parameter to EDF */

  /* do the system call and return the result */
  return (_syscall(MM, RT_SET_SCHED, &m));
}    
