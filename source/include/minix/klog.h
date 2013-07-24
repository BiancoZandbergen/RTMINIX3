/* Main header file for kernel logging.
 * Processes using this functionality must be linked with libklog
 */

#ifndef KLOG_H
#define KLOG_H

/* number of entries in the kernel log */
#define KLOG_SIZE 1024

/* message fields */
#define KLOG_STATE m1_i1
#define KLOG_TYPE  m1_i2
#define KLOG_ENDPT m1_i1
#define KLOG_PTR   m1_p1

/* kernel log type */
#define KLOG_CONTEXTSWITCH  1
#define KLOG_CLOCKINT       2

/* declaration of the kernel log entry structure */
struct klog_entry {
    int klog_time;
    int klog_endpoint;
    char klog_type;
    char klog_name[8];
    int klog_data;
};    

#ifndef _SYSTEM
/* library function prototypes */
int klog_set(int type);
int klog_copy(void *data);
#endif

#endif

