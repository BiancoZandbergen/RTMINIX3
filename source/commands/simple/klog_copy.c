#include <stdio.h>
#include <minix/klog.h>

struct klog_entry klog[KLOG_SIZE];

int main(void)
{
    int i;

    if (klog_copy(&klog) != 0) {
        printf("Copying kernel log failed!\n");
        return -1;
    }

    for (i=0;i<KLOG_SIZE;i++) {
        printf("%d %d %s\n", klog[i].klog_time, klog[i].klog_endpoint, klog[i].klog_name);
    }

    return 0;
        
}
