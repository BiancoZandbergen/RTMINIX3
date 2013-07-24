/* The library function implemented in this file:
 *   klog_copy 
 *
 * Function description:
 *   This function copies the kernel log from the kernel
 *   to the user program.
 * 
 * The parameters for this library function are:
 *   data: a pointer to an array of struct klog_entry with the size of KLOG_SIZE
 *
 * Return value:
 *   Returns 0 if the operation succeeded.
 *   If the return value is not 0 the error code
 *   is saved in errno.
 */
#include <lib.h>
#include <minix/klog.h>

int klog_copy(void *data)
{
  message m; /* message we use for the system call */
    
  m.KLOG_PTR = data; /* set the pointer to the kernel log in the user program */
    
  /* do the system call and return the result */
  return (_syscall(MM, KLOG_COPY, &m));
}    

