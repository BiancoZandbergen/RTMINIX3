#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <minix/rt.h>

int main(int argc, char *argv[])
{
    int cycles;
    int priority;
    unsigned int i;
    unsigned int j;
    

    if (argc != 3) {
        printf("Wrong number of parameters\n");
        printf("parameters: <priority> <cycles>\n");
        return -1;
    }

    priority = atoi(argv[1]);
    cycles = atoi(argv[2]);
    
    
    if (rt_set_rm(priority) != 0) {
        printf("rt_set_rm() failed!\n");
        return -1;
    }

    while (1) {
        for (i=0; i<cycles;i++) {
            for (j=0;j<1000000;j++);
        }

        sleep(1);    
            
    }

    return 0;
}
        


