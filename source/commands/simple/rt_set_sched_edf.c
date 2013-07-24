#include <stdio.h>
#include <minix/rt.h>

int main(void)
{
    if (rt_set_sched_edf() == 0) {
        printf("RT scheduler set to EDF\n");
        return 0;
    } else {
        printf("Setting RT scheduler to EDF failed!\n");
        return 1;
    }   
}
