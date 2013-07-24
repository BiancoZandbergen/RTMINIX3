#include <stdio.h>
#include <minix/klog.h>

int main(void)
{
    if (klog_set(KLOG_CONTEXTSWITCH) != 0) {
        printf("Enabling kernel log (on context switch) failed!\n");
        return -1;
    }

    return 0;
}
