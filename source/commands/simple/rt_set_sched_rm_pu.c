#include <stdio.h>
#include <minix/rt.h>

int main(void)
{
    if (rt_set_sched_rm(PRIO_UNIQUE) == 0) {
        printf("RT scheduler set to RM prio unique\n");
        return 0;
    } else {
        printf("Setting RT scheduler to RM prio unique failed!\n");
        return 1;
    }   
}
