
/* Author: Ben Gras <beng@few.vu.nl>  17 march 2006 */

/* Modified top to display information for edf processes
 * called edftop, by Bianco Zandbergen (20 june 2009)
 */
#define _MINIX 1
#define _POSIX_SOURCE 1

#include <stdio.h>
#include <pwd.h>
#include <curses.h>
#include <timers.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <termcap.h>
#include <termios.h>
#include <time.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

#include <sys/ioc_tty.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>

#include <minix/ipc.h>
#include <minix/config.h>
#include <minix/type.h>
#include <minix/const.h>

#include <math.h>

#include "../../servers/pm/mproc.h"
#include "../../kernel/const.h"
#include "../../kernel/proc.h"

#define  TC_BUFFER  1024        /* Size of termcap(3) buffer    */
#define  TC_STRINGS  200        /* Enough room for cm,cl,so,se  */

char *Tclr_all;

int print_memory(struct pm_mem_info *pmi)
{
        int h;
        int largest_bytes = 0, total_bytes = 0; 
        for(h = 0; h < _NR_HOLES; h++) {
                if(pmi->pmi_holes[h].h_base && pmi->pmi_holes[h].h_len) {
                        int bytes;
                        bytes = pmi->pmi_holes[h].h_len << CLICK_SHIFT;
                        if(bytes > largest_bytes) largest_bytes = bytes;
                        total_bytes += bytes;
                }
        }

    printf("Mem: %dK Free, %dK Contiguous Free\n",
        total_bytes/1024, largest_bytes/1024);

    return 1;
}

int print_load(double *loads, int nloads)
{
    int i;
    printf("load averages: ");
    for(i = 0; i < nloads; i++)
        printf("%s %.2f", (i > 0) ? "," : "", loads[i]);
    printf("\n");
    return 1;
}

#define PROCS (NR_PROCS+NR_TASKS)

int print_proc_summary(struct proc *proc)
{
    int p, alive, running, sleeping;

    alive = running = sleeping = 0;

    for(p = 0; p < PROCS; p++) {
        if(p - NR_TASKS == IDLE)
            continue;
        if(proc[p].p_rts_flags & SLOT_FREE)
            continue;
        alive++;
        if(proc[p].p_rts_flags & ~SLOT_FREE)
            sleeping++;
        else
            running++;
    }
    printf("%d processes: %d running, %d sleeping\n",
        alive, running, sleeping);
    return 1;
}

static struct tp {
    struct proc *p;
    int ticks;
} tick_procs[PROCS];

int cmp_ticks(const void *v1, const void *v2)
{
    struct tp *p1 = (struct tp *) v1, *p2 = (struct tp *) v2;
    if(p1->ticks < p2->ticks)
        return 1;
    if(p1->ticks > p2->ticks)
        return -1;
    if(p1->p->p_nr < p2->p->p_nr)
        return -1;
    if(p1->p->p_nr > p2->p->p_nr)
        return 1;
    return 0;
}

void print_procs(int maxlines,
    struct proc *proc1, struct proc *proc2, int dt,
    struct mproc *mproc)
{
    int p, nprocs, tot=0;
    int idleticks = 0, kernelticks = 0, systemticks = 0;

    if(dt < 1) return;

    for(p = nprocs = 0; p < PROCS; p++) {
        if(proc2[p].p_rts_flags & SLOT_FREE)
            continue;
        tick_procs[nprocs].p = proc2 + p;
        if(proc1[p].p_endpoint == proc2[p].p_endpoint) {
            tick_procs[nprocs].ticks =
                proc2[p].p_user_time-proc1[p].p_user_time;
        } else {
            tick_procs[nprocs].ticks =
                proc2[p].p_user_time;
        }
        if(p-NR_TASKS == IDLE) {
            idleticks = tick_procs[nprocs].ticks;
            continue;
        }

        /* Kernel task time, not counting IDLE */
        if(proc2[p].p_nr < 0)
            kernelticks += tick_procs[nprocs].ticks;
        else if(mproc[proc2[p].p_nr].mp_procgrp == 0)
            systemticks += tick_procs[nprocs].ticks;
        nprocs++;
    }

    qsort(tick_procs, nprocs, sizeof(tick_procs[0]), cmp_ticks);

    printf("CPU states: %6.2f%% user, %6.2f%% system, %6.2f%% kernel, %6.2f%% idle",
        100.0*(dt-systemticks-kernelticks-idleticks)/dt,
        100.0*systemticks/dt,
        100.0*kernelticks/dt,
        100.0*idleticks/dt);
    printf("\n\n");
    maxlines -= 2;

    printf("PNR   ENDPT  ST PERIOD CTIME  PRD#  TLP TLNP     USED RESERVED  %%U MD COMMAND\n");
    maxlines--;

    /* prints EDF process list */
    for(p=0; p < PROCS; p++) {
        if (proc2[p].p_rts_flags & SLOT_FREE) continue;
       
        if (proc2[p].p_rt != 1) continue;
        
        if (maxlines-- <= 0) break;
        
        /* print state */
        printf("%3d", proc2[p].p_nr);

        /* print endpoint */
        printf(" %7d", proc2[p].p_endpoint);
        
        /* print state */
        if (proc2[p].p_rts_flags == 0) {
            printf(" RUN");
        } else if (proc2[p].p_rts_flags & NEXTPERIOD) {
            printf(" WNP");
        } else if (proc2[p].p_rts_flags != 0) {
            printf(" BLK");
        } else {    
            printf("       ");
        }    

        /* print period in ticks */
        printf(" %6d", proc2[p].p_rt_period);

        /* print calculation time per period in ticks */
        printf(" %5d", proc2[p].p_rt_calctime);

        /* print current period number (unfinished period) */
        printf(" %5u", proc2[p].p_rt_periodnr);

        /* print calculation time left in current period */
        printf(" %4d", proc2[p].p_rt_ticksleft);

        /* print ticks till next period start (deadline) */
        printf(" %4d", proc2[p].p_rt_nextperiod);

        /* print total used ticks and total reserved ticks */
        printf(" %8u %8u", proc2[p].p_rt_totalused, proc2[p].p_rt_totalreserved);

        /* print percentage of ticks used */
        if (proc2[p].p_rt_totalused == 0 || proc2[p].p_rt_totalreserved == 0) {
            printf("  ??"); /* prevent divide by zero */
        } else {
            printf(" %3.0f", (float)((float)(proc2[p].p_rt_totalused / (float)proc2[p].p_rt_totalreserved) * (float)100));
        }
        
        /* print missed deadlines */
        printf(" %2u", proc2[p].p_rt_missed_dl);
        
        /* print process name */
        printf(" %s\n", proc2[p].p_name);
    }
}

void showtop(int r)
{
#define NLOADS 3
    double loads[NLOADS];
    int nloads, i, p, lines = 0;
    static struct proc prev_proc[PROCS], proc[PROCS];
    struct winsize winsize;
        static struct pm_mem_info pmi;
    static int prev_uptime, uptime;
    static struct mproc mproc[NR_PROCS];
    struct tms tms;

    uptime = times(&tms);

    if(ioctl(STDIN_FILENO, TIOCGWINSZ, &winsize) != 0) {
        perror("TIOCGWINSZ");
        fprintf(stderr, "TIOCGWINSZ failed\n");
        exit(1);
    }

        if(getsysinfo(PM_PROC_NR, SI_MEM_ALLOC, &pmi) < 0) {
        fprintf(stderr, "getsysinfo() for SI_MEM_ALLOC failed.\n");
        exit(1);;
    }

    if(getsysinfo(PM_PROC_NR, SI_KPROC_TAB, proc) < 0) {
        fprintf(stderr, "getsysinfo() for SI_KPROC_TAB failed.\n");
        exit(1);
    }

    if(getsysinfo(PM_PROC_NR, SI_PROC_TAB, mproc) < 0) {
        fprintf(stderr, "getsysinfo() for SI_PROC_TAB failed.\n");
        exit(1);
    }

    if((nloads = getloadavg(loads, NLOADS)) != NLOADS) {
        fprintf(stderr, "getloadavg() failed - %d loads\n", nloads);
        exit(1);
    }


    printf("%s", Tclr_all);

    lines += print_load(loads, NLOADS);
    lines += print_proc_summary(proc);
    lines += print_memory(&pmi);

    if(winsize.ws_row > 0) r = winsize.ws_row;

    print_procs(r - lines - 2, prev_proc,
        proc, uptime-prev_uptime, mproc);

    memcpy(prev_proc, proc, sizeof(prev_proc));
    prev_uptime = uptime;
}

void init(int *rows)
{
    char  *term;
    static char   buffer[TC_BUFFER], strings[TC_STRINGS];
    char *s = strings, *v;

    *rows = 0;

    if(!(term = getenv("TERM"))) {
        fprintf(stderr, "No TERM set\n");
        exit(1);
    }

    if ( tgetent( buffer, term ) != 1 ) {
        fprintf(stderr, "tgetent failed for term %s\n", term);
        exit(1);
    }

    if ( (Tclr_all = tgetstr( "cl", &s )) == NULL )
        Tclr_all = "\f";

    if((v = tgetstr ("li", &s)) != NULL)
        sscanf(v, "%d", rows);
    if(*rows < 1) *rows = 24;
    if(!initscr()) {
        fprintf(stderr, "initscr() failed\n");
        exit(1);
    }
    cbreak();
    nl();
}

void sigwinch(int sig) { }

int main(int argc, char *argv[])
{
    int r, c, s = 0, orig;

    init(&r);

    while((c=getopt(argc, argv, "s:")) != EOF) {
        switch(c) {
            case 's':
                s = atoi(optarg);
                break;
            default:
                fprintf(stderr,
                    "Usage: %s [-s<secdelay>]\n", argv[0]);
                return 1;
        }
    }

    if(s < 1) 
        s = 2;

    /* Catch window size changes so display is updated properly right away. */
    signal(SIGWINCH, sigwinch);

    while(1) {
        fd_set fds;
        int ns;
        struct timeval tv;
        showtop(r);
        tv.tv_sec = s;
        tv.tv_usec = 0;

        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        if((ns=select(STDIN_FILENO+1, &fds, NULL, NULL, &tv)) < 0
            && errno != EINTR) {
            perror("select");
            sleep(1);
        }

        if(ns > 0 && FD_ISSET(STDIN_FILENO, &fds)) {
            char c;
            if(read(STDIN_FILENO, &c, 1) == 1) {
                switch(c) {
                    case 'q':
                        return 0;
                        break;
                }
            }
        }
    }

    return 0;
}

