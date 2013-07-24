/* The library function implemented in this file:
 *   klog_set
 *
 * Function description:
 *   This function sets the kernel logger state to 1.
 *   This means that the kernel will start with logging
 *   untill the buffer is full.
 * 
 * The parameters for this library function are:
 *   type       The type of event to log.
 *              KLOG_CONTEXTSWITCH to log the next running
 *              process on every context switch.
 *              KLOG_CLOCKINT to log the current running process
 *              on every clock interrupt.
 *
 * Return value:
 *   Returns 0 if the operation succeeded.
 *   If the return value is not 0 the error code
 *   is saved in errno.
 */
#include <lib.h>
#include <minix/klog.h>

int klog_set(int type)
{
  message m; /* message we use for the system call */
  m.KLOG_STATE = 1; /* set the state to 1 */
  m.KLOG_TYPE = type; /* what to log? */

  /* do the system call and return the result */
  return (_syscall(MM, KLOG_SET, &m));
}    

