/* System calls for real-time.	Author: Bianco Zandbergen
 *								19 May 2009
 * The entry points into this file are:
 *   do_rt_set_sched: set the real-time scheduler type
 *   do_rt_set: transform a normal process to real-time process
 *   do_rt_nextperiod: give up remaining calculation time for EDF processes
 *   do_rt_set_sched_bridge: set RT scheduling bridge state
 */

#include "pm.h"
#include <minix/rt.h>

/*===========================================================================*
 *				do_rt_set_sched				                                 *
 *===========================================================================*/
PUBLIC int do_rt_set_sched(void)
{
  /* Set the Real-time scheduler to use.
   * This setting is system wide and all real-time processes should use the same
   * RT scheduler.
   */
  if (m_in.RT_SCHED == SCHED_EDF) {
      /* Received a request to set the RT scheduler to Earliest Deadline First.
       * Invoke the system library function to do the kernel call and
       * return the result.
       * The second parameter is only used by RM, so we set it to 0.
       */
      return (sys_rt_set_sched(SCHED_EDF, 0));
  } else if (m_in.RT_SCHED == SCHED_RM) {
      /* Received a request to set the RT scheduler to Rate-Monotonic.
       * Invoke the system library function that will do the kernel call and
       * return the result.
       * The second parameter defines wether a RM priority should be unique or not.
       */
      return (sys_rt_set_sched(SCHED_RM, m_in.RM_PRIO_POLICY)); 
  } else {
      /* unknown scheduler type */
      return (EINVAL);
  }    
}	

/*===========================================================================*
 *				do_rt_set   				                                 *
 *===========================================================================*/
PUBLIC int do_rt_set(void)
{
  /* Transform a non real-time process to real-time.
   * The scheduler type should equal to the current RT scheduler set by
   * do_rt_set_sched(), checks for this are done in the kernel.
   */
  switch (m_in.RT_SCHED) {
      case SCHED_RM:
          /* Process wants to be real-time and use Rate-Monotonic scheduling.
           * Invoke the system library function to do the kernel call and return 
           * the result. m_in.m_source is the endpoint of the process that called
           * the system call. Rate-Monotonic processes will have a RM priority besides
           * the Minix scheduling priority. All RM processes share the same Minix priority.
           * The priority among RM processes is defined by the RM priority.
           * Last parameter is not used so we set it to 0.
           */
          return (sys_rt_set(m_in.m_source, SCHED_RM, m_in.RM_PRIO, 0));
      case SCHED_EDF:
          /* Process wants to be real-time and use Earliest Deadline First scheduling.
           * Invoke the system library function to do the kernel call and return the
           * result. An EDF process is a periodic process, so we specify the period in
           * system ticks. Within each period the process reserves calculation time that
           * is also specified in ticks. If an EDF process does not get the calculation time
           * it reserved before a new period starts it has missed a deadline.
           */     
          return (sys_rt_set(m_in.m_source, SCHED_EDF, m_in.EDF_PERIOD, m_in.EDF_CALCTIME));    
      default:
          /* unknown scheduler type */
          return (EINVAL);
  }         
}    

/*===========================================================================*
 *				do_rt_nextperiod			                                 *
 *===========================================================================*/
PUBLIC int do_rt_nextperiod(void)
{
  /* Give up remaining calculation time and wait till next period start. 
   * This system call may only be used by processes that are scheduled 
   * using Earliest Deadline First.
   * Invoke the system library function to do the kernel call and return the result.
   * m_in.m_source is the endpoint of the requestion process.
   */  
  return (sys_rt_nextperiod(m_in.m_source));
}    

/*===========================================================================*
 *				do_rt_set_sched_bridge		                                 *
 *===========================================================================*/
PUBLIC int do_rt_set_sched_bridge(void)
{
  /* Set the real-time scheduling bridge state.
   * m_in.RT_SCHED_BRIDGE is the state that the requesting process wants it
   * to set to. Invokes the system library function to do the kernel call
   * and return the result. Process priorities can be defined in three parts:
   * highest priority are system processes, second highest priority is for real-time
   * processes and lowest priorities are for normal user processes. If state is set to 0
   * system processes are not allowed to get a lower priority than real-time processes.
   * If the state is set to 1 they can. A system process can get a lower priority if it uses the
   * full quantum. System starts up with state set to 0. Before shutdown the state will be set by shutdown 
   * to 1 otherwise the system will not proper shutdown. 
   * This is the only reason for the existance of this functionality.
   */
  return (sys_rt_sched_bridge(m_in.RT_SCHED_BRIDGE));
}   

