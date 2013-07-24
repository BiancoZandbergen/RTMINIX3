/* The library function implemented in this file:
 *   rt_nextperiod
 *
 * Function description:
 *   This function gives processes using Earliest
 *   Deadline First scheduling a way to give up
 *   remaining calculation time. (This function may
 *   only be used by processes using EDF scheduling!)
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

int rt_nextperiod(void)
{
  message m; /* message we use for the system call */

  /* do the system call and return the result */
  return (_syscall(MM, RT_NEXTPERIOD, &m));
}

