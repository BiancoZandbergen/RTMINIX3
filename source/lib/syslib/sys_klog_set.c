/* The system library function implemented in this file:
 *   sys_klog_set
 *
 * Function description:
 *   This function does the kernel call to set the
 *   kernel logger state. If state is set to 1
 *   the kernel will log until the buffer is full.
 * 
 * The parameters for this library function are:
 *   state:     kernel logger state
 *   type:      what to log?
 *
 * Return value:
 *   Returns 0 if the operation succeeded.
 *   If the return value is not 0 the error code
 *   is returned.
 */
#include "syslib.h"
#include <minix/klog.h>

int sys_klog_set(int state, int type)
{
  message m; /* message we use for the kernel call */
  
  m.KLOG_STATE = state; /* set the kernel logger state */
  m.KLOG_TYPE = type; /* what to log? */
  
  /* do the kernel call and return the result */
  return (_taskcall(SYSTASK, SYS_KLOG_SET, &m));
} 

