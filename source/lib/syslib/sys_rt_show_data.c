/* The system library function implemented in this file:
 *   sys_rt_show_data
 *
 * Function description:
 *   This function does a kernel call to dump 
 *   real-time scheduler info.
 * 
 * The parameters for this library function are:
 *   none
 *
 * Return value:
 *   Returns 0 if the operation succeeded.
 *   If the return value is not 0 the error code
 *   is returned.
 */
#include "syslib.h"
#include <minix/rt.h>

int sys_rt_show_data(void)
{
  message m; /* message we use for the kernel call */
  
  /* do the kernel call and return the result */
  return (_taskcall(SYSTASK, SYS_RT_SHOW_DATA, &m));
}    

