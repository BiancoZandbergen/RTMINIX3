/* The system library function implemented in this file:
 *   sys_rt_set
 *
 * Function description:
 *   This function will do the kernel call to transform a normal
 *   user process into a real-time process.
 * 
 * The parameters for this library function are:
 *   endpoint:      endpoint of process that wants to be real-time
 *   sched:         scheduler type
 *   param1:        if RM: RM prio if EDF: period
 *   param2:        if EDF: calculation time
 *   
 * Return value:
 *   Returns 0 if the operation succeeded.
 *   If the return value is not 0 the error code
 *   is returned.
 */
#include "syslib.h"
#include <minix/rt.h>

#define PARAM_RM_PRIO         param1
#define PARAM_EDF_PERIOD      param1
#define PARAM_EDF_CALCTIME    param2

int sys_rt_set(int endpoint, int sched, int param1, int param2)
{
  message m; /* message we use for the kernel call */
  
  m.RT_ENDPT = endpoint; /* set the endpoint of the process that wants to be RT */
  m.RT_SCHED = sched; /* set the scheduler */
  
  if (sched == SCHED_RM) {
      
      /* Rate-Monotonic specific parameters */
      m.RM_PRIO = PARAM_RM_PRIO; /* set priority policy */
  } else if (sched == SCHED_EDF) {
      
      /* Earliest Deadline First specific parameters */
      m.EDF_PERIOD = PARAM_EDF_PERIOD; /* set the period in ticks */
      m.EDF_CALCTIME = PARAM_EDF_CALCTIME; /* set the calculation time per period in ticks */
  } else {
      /* unknown scheduler type */
      return (EINVAL);
  }    
  
  /* do the kernel call and return the result */
  return (_taskcall(SYSTASK, SYS_RT_SET, &m));
}    

