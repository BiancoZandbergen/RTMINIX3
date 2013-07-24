/* The system library function implemented in this file:
 *   sys_klog_copy
 *
 * Function description:
 *   This function does the kernel call to
 *   copy the kernel log from the kernel
 *   to a user program.
 * 
 * The parameters for this library function are:
 *   endpoint:      endpoint of user program
 *   data_ptr:      (virtual) pointer to kernel log in user program
 *
 * Return value:
 *   Returns 0 if the operation succeeded.
 *   If the return value is not 0 the error code
 *   is returned.
 */
#include "syslib.h"
#include <minix/klog.h>

int sys_klog_copy(int endpoint, void *data_ptr)
{
  message m; /* message we use for the kernel call */
  
  m.KLOG_ENDPT = endpoint; /* endpoint of user program */
  m.KLOG_PTR = data_ptr; /* pointer to kernel log in user program */
  
  /* do the kernel call and return the result */
  return (_taskcall(SYSTASK, SYS_KLOG_COPY, &m));
} 

