#define NCALLS		  95	/* number of system calls allowed */

/* call nrs for RTMINIX3 */
#define RT_SET_SCHED  45
#define RT_SET        57  
#define RT_NEXTPERIOD 58
#define RT_SET_SCHED_BRIDGE 64
#define KLOG_SET      49
#define KLOG_COPY     50

#define EXIT		   1 
#define FORK		   2 
#define READ		   3 
#define WRITE		   4 
#define OPEN		   5 
#define CLOSE		   6 
#define WAIT		   7
#define CREAT		   8 
#define LINK		   9 
#define UNLINK		  10 
#define WAITPID		  11
#define CHDIR		  12 
#define TIME		  13
#define MKNOD		  14 
#define CHMOD		  15 
#define CHOWN		  16 
#define BRK		  17
#define STAT		  18 
#define LSEEK		  19
#define GETPID		  20
#define MOUNT		  21 
#define UMOUNT		  22 
#define SETUID		  23
#define GETUID		  24
#define STIME		  25
#define PTRACE		  26
#define ALARM		  27
#define FSTAT		  28 
#define PAUSE		  29
#define UTIME		  30 
#define ACCESS		  33 
#define SYNC		  36 
#define KILL		  37
#define RENAME		  38
#define MKDIR		  39
#define RMDIR		  40
#define DUP		  41 
#define PIPE		  42 
#define TIMES		  43
#define SYMLINK		  45
#define SETGID		  46
#define GETGID		  47
#define SIGNAL		  48
#define RDLNK		  49
#define LSTAT		  50
#define IOCTL		  54
#define FCNTL		  55
#define EXEC		  59
#define UMASK		  60 
#define CHROOT		  61 
#define SETSID		  62
#define GETPGRP		  63

/* The following are not system calls, but are processed like them. */
#define UNPAUSE		  65	/* to MM or FS: check for EINTR */
#define REVIVE	 	  67	/* to FS: revive a sleeping process */
#define TASK_REPLY	  68	/* to FS: reply code from tty task */

/* Posix signal handling. */
#define SIGACTION	  71
#define SIGSUSPEND	  72
#define SIGPENDING	  73
#define SIGPROCMASK	  74
#define SIGRETURN	  75

#define REBOOT		  76	/* to PM */

/* MINIX specific calls, e.g., to support system services. */
#define SVRCTL		  77
#define PROCSTAT          78    /* to PM */
#define GETSYSINFO	  79	/* to PM or FS */
#define GETPROCNR         80    /* to PM */
#define DEVCTL		  81    /* to FS */
#define FSTATFS	 	  82	/* to FS */
#define ALLOCMEM	  83	/* to PM */
#define FREEMEM		  84	/* to PM */
#define SELECT            85	/* to FS */
#define FCHDIR            86	/* to FS */
#define FSYNC             87	/* to FS */
#define GETPRIORITY       88	/* to PM */
#define SETPRIORITY       89	/* to PM */
#define GETTIMEOFDAY      90	/* to PM */
#define SETEUID		  91	/* to PM */
#define SETEGID		  92	/* to PM */
#define TRUNCATE	  93	/* to FS */
#define FTRUNCATE	  94	/* to FS */
