/* This file contains the clock task, which handles time related functions.
 * Important events that are handled by the CLOCK include setting and 
 * monitoring alarm timers and deciding when to (re)schedule processes. 
 * The CLOCK offers a direct interface to kernel processes. System services 
 * can access its services through system calls, such as sys_setalarm(). The
 * CLOCK task thus is hidden from the outside world.  
 *
 * Changes:
 *   May 19, 2009   Support for real-time scheduling (EDF and RM) (Bianco Zandbergen)
 *   Oct 08, 2005   reordering and comment editing (A. S. Woodhull)
 *   Mar 18, 2004   clock interface moved to SYSTEM task (Jorrit N. Herder) 
 *   Sep 30, 2004   source code documentation updated  (Jorrit N. Herder)
 *   Sep 24, 2004   redesigned alarm timers  (Jorrit N. Herder)
 *
 * The function do_clocktick() is triggered by the clock's interrupt 
 * handler when a watchdog timer has expired or a process must be scheduled. 
 *
 * In addition to the main clock_task() entry point, which starts the main 
 * loop, there are several other minor entry points:
 *   clock_stop:	called just before MINIX shutdown
 *   get_uptime:	get realtime since boot in clock ticks
 *   set_timer:		set a watchdog timer (+)
 *   reset_timer:	reset a watchdog timer (+)
 *   read_clock:	read the counter of channel 0 of the 8253A timer
 *
 * (+) The CLOCK task keeps tracks of watchdog timers for the entire kernel.
 * The watchdog functions of expired timers are executed in do_clocktick(). 
 * It is crucial that watchdog functions not block, or the CLOCK task may
 * be blocked. Do not send() a message when the receiver is not expecting it.
 * Instead, notify(), which always returns, should be used. 
 */

#include "kernel.h"
#include "proc.h"
#include <signal.h>
#include <minix/com.h>
#include <minix/rt.h>
#include <minix/klog.h>

/* Function prototype for PRIVATE functions. */ 
FORWARD _PROTOTYPE( void init_clock, (void) );
FORWARD _PROTOTYPE( int clock_handler, (irq_hook_t *hook) );
FORWARD _PROTOTYPE( int do_clocktick, (message *m_ptr) );
FORWARD _PROTOTYPE( void load_update, (void));

/* Clock parameters. */
#define COUNTER_FREQ (2*TIMER_FREQ) /* counter frequency using square wave */
#define LATCH_COUNT     0x00	/* cc00xxxx, c = channel, x = any */
#define SQUARE_WAVE     0x36	/* ccaammmb, a = access, m = mode, b = BCD */
				/*   11x11, 11 = LSB then MSB, x11 = sq wave */
#define TIMER_COUNT ((unsigned) (TIMER_FREQ/HZ)) /* initial value for counter*/
#define TIMER_FREQ  1193182L	/* clock frequency for timer in PC and AT */

#define CLOCK_ACK_BIT	0x80	/* PS/2 clock interrupt acknowledge bit */

/* The CLOCK's timers queue. The functions in <timers.h> operate on this. 
 * Each system process possesses a single synchronous alarm timer. If other 
 * kernel parts want to use additional timers, they must declare their own 
 * persistent (static) timer structure, which can be passed to the clock
 * via (re)set_timer().
 * When a timer expires its watchdog function is run by the CLOCK task. 
 */
PRIVATE timer_t *clock_timers;		/* queue of CLOCK timers */
PRIVATE clock_t next_timeout;		/* realtime that next timer expires */

/* The time is incremented by the interrupt handler on each clock tick. */
PRIVATE clock_t realtime;		/* real time clock */
PRIVATE irq_hook_t clock_hook;		/* interrupt handler hook */

/*===========================================================================*
 *				clock_task				     *
 *===========================================================================*/
PUBLIC void clock_task()
{
/* Main program of clock task. If the call is not HARD_INT it is an error.
 */
  message m;			/* message buffer for both input and output */
  int result;			/* result returned by the handler */

  init_clock();			/* initialize clock task */

  /* Main loop of the clock task.  Get work, process it. Never reply. */
  while (TRUE) {

      /* Go get a message. */
      receive(ANY, &m);	

      /* Handle the request. Only clock ticks are expected. */
      switch (m.m_type) {
      case HARD_INT:
          result = do_clocktick(&m);	/* handle clock tick */
          break;
      default:				/* illegal request type */
          kprintf("CLOCK: illegal request %d from %d.\n", m.m_type,m.m_source);
      }
  }
}

/*===========================================================================*
 *				do_clocktick				     *
 *===========================================================================*/
PRIVATE int do_clocktick(m_ptr)
message *m_ptr;				/* pointer to request message */
{
register struct proc **xpp;
register struct proc *temp_p;
/* Despite its name, this routine is not called on every clock tick. It
 * is called on those clock ticks when a lot of work needs to be done.
 */

  /* A process used up a full quantum. The interrupt handler stored this
   * process in 'prev_ptr'.  First make sure that the process is not on the 
   * scheduling queues.  Then announce the process ready again. Since it has 
   * no more time left, it gets a new quantum and is inserted at the right 
   * place in the queues.  As a side-effect a new process will be scheduled.
   */ 
  if (prev_ptr->p_ticks_left <= 0 && priv(prev_ptr)->s_flags & PREEMPTIBLE) {
      lock_dequeue(prev_ptr);		/* take it off the queues */
      lock_enqueue(prev_ptr);		/* and reinsert it again */ 
  }

  /* Check if a clock timer expired and run its watchdog function. */
  if (next_timeout <= realtime) { 
  	tmrs_exptimers(&clock_timers, realtime, NULL);
  	next_timeout = clock_timers == NULL ? 
		TMR_NEVER : clock_timers->tmr_exp_time;
  }

  /* Unfortunately we don't know what event triggered do_clocktick.
   * If the real-time scheduler is EDF we will have to check for the following things:
   * - The current scheduled EDF process has missed the deadline.
   * - The current EDF process has no ticks left in this period.
   * - Check for processes in the wait queue from which a new period starts.     
   */   
  if (rt_sched == SCHED_EDF) {

      /* Check for missed deadline of currently scheduled EDF proc.
       * This is the case if there is a EDF process scheduled AND
       * that process has ticks left in this period AND the number of ticks left
       * till next period is 0. The number of ticks left till next period equals the deadline.
       */
      if (edf_rp != NIL_PROC && edf_rp->p_rt_ticksleft > 0 && edf_rp->p_rt_nextperiod == 0) {
          
          /* Remove EDF process from scheduling queue */
          lock_dequeue(edf_rp);
          
          /* update total used ticks before ticksleft will be reset */
          edf_rp->p_rt_totalused += (edf_rp->p_rt_calctime - edf_rp->p_rt_ticksleft);
          
          /* New period for this process starts immiately because
           * a deadline is the same as a new period start.
           */
          edf_rp->p_rt_nextperiod = edf_rp->p_rt_period;

          /* New period new calculation time */
          edf_rp->p_rt_ticksleft = edf_rp->p_rt_calctime;

          /* update period counter for stats */
          edf_rp->p_rt_periodnr++;

          /* update deadline counter for stats */
          edf_rp->p_rt_missed_dl++;

          /* update total reserved ticks for stats*/
          edf_rp->p_rt_totalreserved += edf_rp->p_rt_calctime;

          /* Add process to the run queue sorted on deadline. 
           * First find the right place in the queue.
           */
          xpp = &edf_run_head;
          while (*xpp != NIL_PROC && (*xpp)->p_rt_nextperiod <= edf_rp->p_rt_nextperiod) {
              xpp = &(*xpp)->p_rt_link;
          }

          /* Add process to the run queue */    
          edf_rp->p_rt_link = *xpp;
          *xpp = edf_rp;

          /* This process is not scheduled any more */
          edf_rp = NIL_PROC;

          /* Check which process has the earliest deadline and may be scheduled now */
          edf_sched();
      }

      /* Check for no ticks left of currently scheduled EDF process. 
       * This is the case if there is an EDF process scheduled AND
       * this process has no ticks left in the current period.
       */
      if (edf_rp != NIL_PROC && edf_rp->p_rt_ticksleft <= 0) {
          
          /* Remove process from scheduling queue */
          lock_dequeue(edf_rp);

          #if 0
          kprintf("do_clocktick: no ticks left: %d\n", edf_rp->p_endpoint);
          #endif 

          /* Add process to the wait queue waiting for next period start.
           * First we have to find the right place in the queue.
           * The queue is sorted on next period start.
           */
          xpp = &edf_wait_head;
          while (*xpp != NIL_PROC && (*xpp)->p_rt_nextperiod <= edf_rp->p_rt_nextperiod) {
              xpp = &(*xpp)->p_rt_link;
          }  

          /* Add process to the wait queue */  
          edf_rp->p_rt_link = *xpp;
          *xpp = edf_rp;

          /* Set the NEXTPERIOD bit in the run time flags.
           * A process is only runnable if p_rts_flags == 0.
           * This ensures that no other code (i.e IPC code)
           * will add the process in the scheduling queue while the 
           * process is still waiting for the next period start.
           */
          edf_rp->p_rts_flags |= NEXTPERIOD;

          /* This process is not scheduled any more */
          edf_rp = NIL_PROC;

          /* Check which process has the earliest deadline and may be scheduled now */
          edf_sched(); 
      }    
     
      /* check for processes with a new period start.
       * We check only the head of the wait queue because the
       * queue is sorted on next period start. If the head of the queue has
       * p_rt_nextperiod == 0 it will be removed from the wait queue and added
       * to the run queue. We will repeat this process until the head of the queue has
       * ticks left till the next period because multiple processes can have a new period start
       * at the same time.
       */
      while (edf_wait_head != NIL_PROC && 
             edf_wait_head->p_rt_nextperiod == 0) {
          
          /* update total ticks used before ticksleft is reset */
          edf_wait_head->p_rt_totalused += (edf_wait_head->p_rt_calctime - edf_wait_head->p_rt_ticksleft);
          
          /* reset the ticks till next period */
          edf_wait_head->p_rt_nextperiod = edf_wait_head->p_rt_period;

          /* reset the calculation time left */
          edf_wait_head->p_rt_ticksleft = edf_wait_head->p_rt_calctime;

          /* This process will be runnable so clear the NEXTPERIOD bit in
           * p_rts_flags.
           */
          edf_wait_head->p_rts_flags &= ~(NEXTPERIOD);
          
          /* increase period counter for stats */
          edf_wait_head->p_rt_periodnr++;

          /* update total reserved ticks for stats */
          edf_wait_head->p_rt_totalreserved += edf_wait_head->p_rt_calctime;
          
          /* Add process to the run queue that is sorted on deadline.
           * First we have to find the right place in the list.
           */
          xpp = &edf_run_head;
          while (*xpp != NIL_PROC && (*xpp)->p_rt_nextperiod <= edf_wait_head->p_rt_nextperiod) {
              xpp = &(*xpp)->p_rt_link;
          }    
          
          /* Add process to the run queue and
           * remove process from wait queue.
           */
          temp_p = edf_wait_head->p_rt_link; /* save the new head of wait queue to temp_p */
          edf_wait_head->p_rt_link = *xpp; /* set the next process pointer of the process we add */
          *xpp = edf_wait_head; /* point to the process we add */
          edf_wait_head = temp_p; /* set the new head of the wait queue, we saved this in temp_p */
          
          /* Because we changed the run queue we will have to check
           * which process has the earliest deadline and should be scheduled now.
           */
          edf_sched();
              
      }     
          
  }   
      
  /* Inhibit sending a reply. */
  return(EDONTREPLY);
}

/*===========================================================================*
 *				init_clock				     *
 *===========================================================================*/
PRIVATE void init_clock()
{
  /* Initialize the CLOCK's interrupt hook. */
  clock_hook.proc_nr_e = CLOCK;

  /* Initialize channel 0 of the 8253A timer to, e.g., 60 Hz, and register
   * the CLOCK task's interrupt handler to be run on every clock tick. 
   */
  outb(TIMER_MODE, SQUARE_WAVE);	/* set timer to run continuously */
  outb(TIMER0, TIMER_COUNT);		/* load timer low byte */
  outb(TIMER0, TIMER_COUNT >> 8);	/* load timer high byte */
  put_irq_handler(&clock_hook, CLOCK_IRQ, clock_handler);
  enable_irq(&clock_hook);		/* ready for clock interrupts */

  /* Set a watchdog timer to periodically balance the scheduling queues. */
  balance_queues(NULL);			/* side-effect sets new timer */
}

/*===========================================================================*
 *				clock_stop				     *
 *===========================================================================*/
PUBLIC void clock_stop()
{
/* Reset the clock to the BIOS rate. (For rebooting.) */
  outb(TIMER_MODE, 0x36);
  outb(TIMER0, 0);
  outb(TIMER0, 0);
}

/*===========================================================================*
 *				clock_handler				     *
 *===========================================================================*/
PRIVATE int clock_handler(hook)
irq_hook_t *hook;
{
/* This executes on each clock tick (i.e., every time the timer chip generates 
 * an interrupt). It does a little bit of work so the clock task does not have 
 * to be called on every tick.  The clock task is called when:
 *
 *	(1) the scheduling quantum of the running process has expired, or
 *	(2) a timer has expired and the watchdog function should be run.
 *
 * Many global global and static variables are accessed here.  The safety of
 * this must be justified. All scheduling and message passing code acquires a 
 * lock by temporarily disabling interrupts, so no conflicts with calls from 
 * the task level can occur. Furthermore, interrupts are not reentrant, the 
 * interrupt handler cannot be bothered by other interrupts.
 * 
 * Variables that are updated in the clock's interrupt handler:
 *	lost_ticks:
 *		Clock ticks counted outside the clock task. This for example
 *		is used when the boot monitor processes a real mode interrupt.
 * 	realtime:
 * 		The current uptime is incremented with all outstanding ticks.
 *	proc_ptr, bill_ptr:
 *		These are used for accounting.  It does not matter if proc.c
 *		is changing them, provided they are always valid pointers,
 *		since at worst the previous process would be billed.
 */
  register unsigned ticks;
  register struct proc *ap; /* used for EDF accounting */
  char call_do_clocktick = 0; /* used for EDF accounting */
  char rq_md = 0; /* has some processed missed deadline in run queue? we need to resort in that case */
  
  /* Acknowledge the PS/2 clock interrupt. */
  if (machine.ps_mca) outb(PORT_B, inb(PORT_B) | CLOCK_ACK_BIT);

  /* Get number of ticks and update realtime. */
  ticks = lost_ticks + 1;
  lost_ticks = 0;
  realtime += ticks;

  /* Update user and system accounting times. Charge the current process for
   * user time. If the current process is not billable, that is, if a non-user
   * process is running, charge the billable process for system time as well.
   * Thus the unbillable process' user time is the billable user's system time.
   */
  proc_ptr->p_user_time += ticks;
  if (priv(proc_ptr)->s_flags & PREEMPTIBLE) {
      proc_ptr->p_ticks_left -= ticks;
  }
  if (! (priv(proc_ptr)->s_flags & BILLABLE)) {
      bill_ptr->p_sys_time += ticks;
      bill_ptr->p_ticks_left -= ticks;

      /* real-time processes don't use p_ticks_left
       * but should they be billed too?
       * We currently don't bill them.
       * Remove the comments to do so.
       * Please note that a process can get a negative
       * p_rt_ticksleft if it can be billed.
       */
      
      /*if (is_rtp(bill_ptr)) {
          bill_ptr->p_rt_ticksleft--;
      }*/    
  }

  /* Update load average. */
  load_update();
  
  /* Kernel schedule logging.
   * Keeps track of all processes running when clock interrupt
   * happens. First we check if we have to log.
   */
  if (klog_state == 1 && klog_type == KLOG_CLOCKINT && klog_ptr < KLOG_SIZE) {
      klog[klog_ptr].klog_data = proc_ptr->p_nr; /* process number */
      klog[klog_ptr].klog_endpoint = proc_ptr->p_endpoint; /* process endpoint */
      klog[klog_ptr].klog_time = get_uptime(); /* time in ticks since boot */
      strcpy(klog[klog_ptr].klog_name, proc_ptr->p_name);   /* name of process */
      klog_ptr++;

      if (klog_ptr >= KLOG_SIZE) {
          /* kernel log buffer is full.
           * We disable logging by setting klog_state to 0.
           * We set klog_ptr to 0 for a next log start.
           */
          kprintf("klog buffer full!\n");
          klog_state = 0;
          klog_ptr = 0;
      }       
  }
  
  /* generic accounting for real-time processes */
  if (is_rtp(proc_ptr)) {
      
      /* make sure quantum never reaches zero.
       * We don't use p_ticks_left for RT processes.
       */
      proc_ptr->p_ticks_left = 100;
  }

  /* if the RT scheduler is EDF
   * we will have to do accounting on
   * all four EDF data structures.
   */
  if (rt_sched == SCHED_EDF) {
          
      /* Do accounting for the currently
       * scheduled EDF process, if there is one.
       */
      if (edf_rp != NIL_PROC) {
              
          /* decrease ticks left in current period */
          edf_rp->p_rt_ticksleft--;
          
          if (edf_rp->p_rt_nextperiod > 0) {
              /* decrease ticks till next period (deadline) */
              edf_rp->p_rt_nextperiod--;
          }
              
          /* check if process has no ticks left
           * in current period AND if the process
           * has missed the deadline. In both cases
           * do_clocktick should be run
           */
          if (edf_rp->p_rt_ticksleft == 0 ||
              edf_rp->p_rt_nextperiod == 0) {
              call_do_clocktick = 1;

              #if EDF_PRINT_MD == 1
              if (edf_rp->p_rt_nextperiod == 0) {
                  kprintf("Process %d %s has missed deadline (edf_rp)\n", edf_rp->p_endpoint, edf_rp->p_name);
              }
              #endif
          }    
      }

      /* Do accounting for the run queue.
       * We will check all processes in the queue.
       */
      ap = edf_run_head;
      while (ap != NIL_PROC) {
          if (ap->p_rt_nextperiod > 0) {
                 
              /* decrease ticks till next period */
              ap->p_rt_nextperiod--;
              
              if (ap->p_rt_nextperiod == 0) {
                  /* No ticks left till next period but the process
                   * has not used all calculation time.
                   * It missed the deadline. We leave the process in the queue
                   * but we start a new period.  
                   */

                  /* update total used ticks before ticksleft will be reset */
                  ap->p_rt_totalused += (ap->p_rt_calctime - ap->p_rt_ticksleft);
                  
                  /* reset ticks left till next period
                   * and calculation time left in current period.
                   */
                  ap->p_rt_nextperiod = ap->p_rt_period; 
                  ap->p_rt_ticksleft = ap->p_rt_calctime;

                  /* update period counter for stats */
                  ap->p_rt_periodnr++;

                  /* update deadline counter for stats */
                  ap->p_rt_missed_dl++;

                  /* update total reserved ticks for stats */
                  ap->p_rt_totalreserved += ap->p_rt_calctime;

                  /* we need to resort the queue */
                  rq_md = 1;

                  #if EDF_PRINT_MD == 1
                  kprintf("Process %d %s has missed deadline (RQ)\n", ap->p_endpoint, ap->p_name);
                  #endif
              }
          }
          ap = ap->p_rt_link; /* get next process in the queue */
      }

      /* If a process has missed the deadline in the run queue, the deadline
       * will be renewed. In that case we will have to resort the run queue to
       * keep it sorted on deadline. We use a bubble sort algorithm here.
       * The c node precedes the a and e node pointing to the node to which the
       * comparisons are being made.
       */
      if (rq_md != 0) {
          struct proc *a = NIL_PROC;
          struct proc *b = NIL_PROC;
          struct proc *c = NIL_PROC;
          struct proc *e = NIL_PROC;
          struct proc *tmp = NIL_PROC;
          
          while(e != edf_run_head->p_rt_link) {
              c = a = edf_run_head;
              b = a->p_rt_link;
 
              while(a != e) {
                  if(a->p_rt_nextperiod > b->p_rt_nextperiod) {
                      if(a == edf_run_head) {
                          tmp = b->p_rt_link;
                          b->p_rt_link = a;
                          a->p_rt_link = tmp;
                          edf_run_head = b;
                          c = b;
                      } else {
                          tmp = b->p_rt_link;
                          b->p_rt_link = a;
                          a->p_rt_link = tmp;
                          c->p_rt_link = b;
                          c = b;
                      }
                  } else {
                      c = a;
                      a = a->p_rt_link;
                  }
                  
                  b = a->p_rt_link;
                  if(b == e) {
                      e = a;
                  }                 
              }
          }
      }

      /* Do accounting for the wait queue.
       * We will check all processes in the queue.
       */
      ap = edf_wait_head;
      while (ap != NIL_PROC) {
          if (ap->p_rt_nextperiod > 0) {
              
              /* decrease ticks till next period */
              ap->p_rt_nextperiod--;
              
              if (ap->p_rt_nextperiod == 0) {
                  /* new period start for this process.
                   * We will have to call do_clocktick.
                   */
                  call_do_clocktick = 1;
              }    
          }
          ap = ap->p_rt_link; /* get next process in the queue */
      }

      /* Do accounting for the block list.
       * We will check all processes in the list.
       */
      ap = edf_block_head;
      while (ap != NIL_PROC) {
          if (ap->p_rt_nextperiod > 0) {
                  
              /* decrease ticks till next period */
              ap->p_rt_nextperiod--;
  
              if (ap->p_rt_nextperiod == 0) {
                  /* No ticks left till next period and the process
                   * has not used all calculation time. The process missed the deadline.
                   * We leave the process in the block list but start a new period.
                   */

                  /* update total used ticks before ticksleft will be reset */
                  ap->p_rt_totalused += (ap->p_rt_calctime - ap->p_rt_ticksleft);
                  
                  /* reset ticks left till next period
                   * and calculation time left in current period.
                   */
                  ap->p_rt_nextperiod = ap->p_rt_period;
                  ap->p_rt_ticksleft = ap->p_rt_calctime;

                  /* update period counter for stats */
                  ap->p_rt_periodnr++;

                  /* update deadline counter for stats */
                  ap->p_rt_missed_dl++;

                  /* update total reserved ticks for stats */
                  ap->p_rt_totalreserved += ap->p_rt_calctime;

                  #if EDF_PRINT_MD
                  kprintf("Process %d %s has missed deadline (BQ)\n", ap->p_endpoint, ap->p_name);
                  #endif
              }
          }
          ap = ap->p_rt_link; /* get next process in the list */
      }    

      /* done with EDF accounting */      
  }    
  
  /* Check if do_clocktick() must be called. Done for alarms and scheduling.
   * Some processes, such as the kernel tasks, cannot be preempted. 
   */ 
  if ((next_timeout <= realtime) || (proc_ptr->p_ticks_left <= 0) || (call_do_clocktick != 0)) {
      prev_ptr = proc_ptr;			/* store running process */
      lock_notify(HARDWARE, CLOCK);		/* send notification */
  } 
  return(1);					/* reenable interrupts */
}

/*===========================================================================*
 *				get_uptime				     *
 *===========================================================================*/
PUBLIC clock_t get_uptime()
{
/* Get and return the current clock uptime in ticks. */
  return(realtime);
}

/*===========================================================================*
 *				set_timer				     *
 *===========================================================================*/
PUBLIC void set_timer(tp, exp_time, watchdog)
struct timer *tp;		/* pointer to timer structure */
clock_t exp_time;		/* expiration realtime */
tmr_func_t watchdog;		/* watchdog to be called */
{
/* Insert the new timer in the active timers list. Always update the 
 * next timeout time by setting it to the front of the active list.
 */
  tmrs_settimer(&clock_timers, tp, exp_time, watchdog, NULL);
  next_timeout = clock_timers->tmr_exp_time;
}

/*===========================================================================*
 *				reset_timer				     *
 *===========================================================================*/
PUBLIC void reset_timer(tp)
struct timer *tp;		/* pointer to timer structure */
{
/* The timer pointed to by 'tp' is no longer needed. Remove it from both the
 * active and expired lists. Always update the next timeout time by setting
 * it to the front of the active list.
 */
  tmrs_clrtimer(&clock_timers, tp, NULL);
  next_timeout = (clock_timers == NULL) ? 
	TMR_NEVER : clock_timers->tmr_exp_time;
}

/*===========================================================================*
 *				read_clock				     *
 *===========================================================================*/
PUBLIC unsigned long read_clock()
{
/* Read the counter of channel 0 of the 8253A timer.  This counter counts
 * down at a rate of TIMER_FREQ and restarts at TIMER_COUNT-1 when it
 * reaches zero. A hardware interrupt (clock tick) occurs when the counter
 * gets to zero and restarts its cycle.  
 */
  unsigned count;

  outb(TIMER_MODE, LATCH_COUNT);
  count = inb(TIMER0);
  count |= (inb(TIMER0) << 8);
  
  return count;
}

/*===========================================================================*
 *				load_update				     * 
 *===========================================================================*/
PRIVATE void load_update(void)
{
	u16_t slot;
	int enqueued = -1, q;	/* -1: special compensation for IDLE. */
	struct proc *p;

	/* Load average data is stored as a list of numbers in a circular
	 * buffer. Each slot accumulates _LOAD_UNIT_SECS of samples of
	 * the number of runnable processes. Computations can then
	 * be made of the load average over variable periods, in the
	 * user library (see getloadavg(3)).
	 */
	slot = (realtime / HZ / _LOAD_UNIT_SECS) % _LOAD_HISTORY;
	if(slot != kloadinfo.proc_last_slot) {
		kloadinfo.proc_load_history[slot] = 0;
		kloadinfo.proc_last_slot = slot;
	}

	/* Cumulation. How many processes are ready now? */
	for(q = 0; q < NR_SCHED_QUEUES; q++)
		for(p = rdy_head[q]; p != NIL_PROC; p = p->p_nextready)
			enqueued++;

	kloadinfo.proc_load_history[slot] += enqueued;

	/* Up-to-dateness. */
	kloadinfo.last_clock = realtime;
}

