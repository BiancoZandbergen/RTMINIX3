/* The system library function implemented in this file:
 *   sys_rt_nextperiod
 *
 * Function description:
 *   This function does the kernel call for processes
 *   scheduled by Earliest Deadline First that wants to
 *   give up remaining calculation time in a period.
 *   The process will wait till the next period start
 *   after this call.
 * 
 * The parameters for this library function are:
 *   endpoint:      endpoint of process that wants to give up calculation time
 *
 * Return value:
 *   Returns 0 if the operation succeeded.
 *   If the return value is not 0 the error code
 *   is returned.
 */
#include "syslib.h"
#include <minix/rt.h>

int sys_rt_nextperiod(int endpoint)
{
  message m; /* message we use for the kernel call */
  
  m.RT_ENDPT = endpoint; /* set the endpoint */
  
  /* do the kernel call and return the result */
  return (_taskcall(SYSTASK, SYS_RT_NEXTPERIOD, &m));
}    

