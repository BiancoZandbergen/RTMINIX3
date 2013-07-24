/* The kernel call implemented in this file:
 *   m_type:    SYS_KLOG_COPY
 *
 * The parameters for this kernel call are:
 *    m1_i1:    KLOG_ENDPT    Endpoint of user program
 *    m1_p1:    KLOG_PTR      (virtual) pointer to kernel log in user program
 */

#include "../system.h"
#include <minix/type.h>
#include <sys/resource.h>
#include <minix/klog.h>

/*===========================================================================*
 *                  do_klog_copy                                             *
 *===========================================================================*/
PUBLIC int do_klog_copy(message *m_ptr)
{
  /* Copy the kernel log from the kernel to a user program. */
    
  size_t length; /* We store the kernel log size in bytes here */
  phys_bytes src_phys; /* We store the physical address of the log in the kernel here */
  phys_bytes dst_phys; /* We store the physical address of the log in the user program here */
  int proc_nr; /* process number of user program */
  
  /* calculate the size of the kernel log which is
   * the size of a struct klog_entry multiplied by the 
   * number of entries in the log. KLOG_SIZE is defined in
   * <minix/klog.h>. This is the number of bytes we are gonna copy.
   */
  length = sizeof(struct klog_entry) * KLOG_SIZE;
  
  /* We can't use virtual memory addresses to copy from kernel to
   * user program. We will have to translate both the source and destination
   * to physical addresses.
   */
  
  /* Translate virtual address of the log in the kernel
   * to the physical address.
   */
  src_phys = vir2phys(&klog);
  
  /* Check if endpoint of user program is valid and get the process number */
  if (! isokendpt(m_ptr->KLOG_ENDPT, &proc_nr)) {
      return (EFAULT);
  }

  /* Translate the virtual address of the log in the user program
   * to the physical address.
   */
  dst_phys = numap_local(proc_nr, (vir_bytes) m_ptr->KLOG_PTR, length);

  /* translating went wrong if this is true */
  if (src_phys == 0 || dst_phys == 0) {
      kprintf("systask: do_klog_copy() src_phys or dst_phys == 0\n");
      return (EFAULT);
  }

  /* finally copy the log to the user program */
  phys_copy(src_phys, dst_phys, length);  
  
  return (OK);    
}

