/* This is the master header for SS.  It includes some other files
 * and defines the principal constants.
 */
#define _POSIX_SOURCE      1	/* tell headers to include POSIX stuff */
#define _MINIX             1	/* tell headers to include MINIX stuff */
#define _SYSTEM            1	/* tell headers that this is the system */

/* The following are so basic, all the *.c files get them automatically. */
#include <minix/config.h>	/* MUST be first */
#include <ansi.h>		/* MUST be second */
#include <sys/types.h>
#include <minix/const.h>
#include <minix/type.h>

#include <fcntl.h>
#include <unistd.h>
#include <minix/syslib.h>
#include <minix/sysutil.h>

#include <limits.h>
#include <errno.h>

#include <minix/sem.h>
#include "proto.h"

#ifndef OK
#define OK 0
#endif

/* number of semaphore supported */
#define NR_SEMS 128

/* semaphore structure */
struct sem {
	int sem_type;
	int value;
	int size;
	int used;
	int owner;
	int user;
	struct sem_proc * listp;
	
};

/* used to save processes that are blocked
 * on a semaphore
 */
struct sem_proc {
	int endpoint;
	int prio;
	struct sem_proc * next;
};

/* semaphore table */
struct sem semtable[NR_SEMS];

/* keep track of sems in use, expirimental */
int used;
	
