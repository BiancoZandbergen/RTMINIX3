/* The kernel call implemented in this file:
 *   m_type:    SYS_RT_SHOW_DATA
 *
 * The parameters for this kernel call are:
 *    none
 */

#include "../system.h"
#include <minix/type.h>
#include <sys/resource.h>
#include <minix/rt.h>


/*===========================================================================*
 *                  do_rt_show_data                                          *
 *===========================================================================*/
PUBLIC int do_rt_show_data(message *m_ptr)
{
  /* dumpe scheduling info if a real-time scheduler is set */
  if (rt_sched != SCHED_UNDEFINED) {
      show_rt_data();
  } else {
      kprintf("No Real-time scheduler set!\n");
  }
  
  return (OK);    
}

