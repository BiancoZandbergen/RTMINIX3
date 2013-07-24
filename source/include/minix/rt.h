/* Main header file for Real-time functionality.
 * Processes using these functionality should be linked with librt.
 */
#ifndef RT_H
#define RT_H

#include <ansi.h>

/* scheduler type definitions */
#define SCHED_UNDEFINED     0
#define SCHED_RM            1
#define SCHED_EDF           2

/* priority policies for Rate-Monotonic */
#define PRIO_UNIQUE         1
#define PRIO_NOT_UNIQUE     2


/* message fields for real-time related system calls */
#define RT_ENDPT        m7_i1
#define RT_SCHED        m7_i2
#define RM_PRIO         m7_i3
#define RM_PRIO_POLICY  m7_i4
#define EDF_PERIOD      m7_i3
#define EDF_CALCTIME    m7_i4
#define RT_SCHED_BRIDGE m1_i1

/* library function prototypes */
_PROTOTYPE( int rt_set_sched_edf, (void) );
_PROTOTYPE( int rt_set_sched_rm, (int prio_policy) );
_PROTOTYPE( int rt_set_edf, (int period, int calctime) );
_PROTOTYPE( int rt_set_rm, (int prio) );
_PROTOTYPE( int rt_set_sched_bridge, (int state) );
_PROTOTYPE( int rt_nextperiod, (void) );

#endif

