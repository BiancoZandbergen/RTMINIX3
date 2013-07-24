/* System calls for kernel logging.	Author: Bianco Zandbergen
 *								    19 May 2009
 * The entry points into this file are:
 *   do_klog_set: set the kernel log state
 *   do_klog_copy: copy the kernel log to a user process
 */

#include "pm.h"
#include <minix/klog.h>

/*===========================================================================*
 *				do_klog_set 				                                 *
 *===========================================================================*/
PUBLIC int do_klog_set(void)
{
  /* Set the kernel log state.
   * Invoke the system library function to do the kernel call.
   */
  return(sys_klog_set(m_in.KLOG_STATE, m_in.KLOG_TYPE));
}	

/*===========================================================================*
 *				do_klog_copy   				                                 *
 *===========================================================================*/
PUBLIC int do_klog_copy(void)
{
  /* Copy the kernel log from the kernel to the user process.
   * Invoke the system library function to do the kernel call.
   * m_in.m_source is the endpoint of the user process.
   * m_in.KLOG_PTR is the pointer to the kernel log data structure
   * of the user process.
   */
  return(sys_klog_copy(m_in.m_source, m_in.KLOG_PTR));
}

