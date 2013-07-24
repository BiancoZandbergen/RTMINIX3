#include <stdio.h>
#include <minix/klog.h>

int main(void)
{
    if (klog_set(KLOG_CLOCKINT) != 0) {
        printf("Enabling kernel log (on clock interrupt) failed!\n");
        return -1;
    }

    return 0;
}
