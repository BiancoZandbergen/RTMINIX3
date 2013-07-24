/* The kernel call implemented in this file:
 *   m_type:    SYS_RT_SCHED_BRIDGE
 *
 * The parameters for this kernel call are:
 *    m1_i1:    RT_SCHED_BRIDGE     Scheduler bridge state
 */

#include "../system.h"
#include <minix/type.h>
#include <sys/resource.h>
#include <minix/rt.h>


/*===========================================================================*
 *                  do_rt_set_sched                                          *
 *===========================================================================*/
PUBLIC int do_rt_set_sched_bridge(message *m_ptr)
{
  /* Set the scheduling bridge state.
   * If set to 0 high priority processes that are lowered in priority
   * are not allowed to get a lower priority than RT processes.
   * If set to 1 they can. Before Minix shutdowns it will set it to 1 because
   * otherwise the system cannot shutdown properly.
   */
  rt_sched_bridge = m_ptr->RT_SCHED_BRIDGE;

  return (OK);    
}

