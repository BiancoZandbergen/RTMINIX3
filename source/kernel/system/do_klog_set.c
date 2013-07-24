/* The kernel call implemented in this file:
 *   m_type:    SYS_KLOG_SET
 *
 * The parameters for this kernel call are:
 *    m1_i1:    KLOG_STATE       Kernel logger state
 *    m1_i2     KLOG_TYPE        Kernel log type
 */

#include "../system.h"
#include <minix/type.h>
#include <sys/resource.h>
#include <minix/klog.h>

/*===========================================================================*
 *                  do_klog_set                                              *
 *===========================================================================*/
PUBLIC int do_klog_set(message *m_ptr)
{

  /* check if the type specified is valid */
  if (m_ptr->KLOG_TYPE != KLOG_CONTEXTSWITCH &&
      m_ptr->KLOG_TYPE != KLOG_CLOCKINT) {
      
      return EINVAL;
  }  
    
  /* Set the kernel logger state.
   * If set to 1 it will log untill the buffer is full.
   * If the buffer is full the state will be set back to 0.
   */
  klog_state = m_ptr->KLOG_STATE;

  /* Set the kernel log type
   * If set to KLOG_CONTEXTSWITCH it will log every process
   * that will run next after a context switch.
   * If set to KLOG_CLOCKINT it will log every process
   * that was running when the clock interrupt happened.
   */
  klog_type = m_ptr->KLOG_TYPE; 
  
  return (OK);    
}


