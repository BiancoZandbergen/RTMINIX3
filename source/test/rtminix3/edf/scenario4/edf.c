#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <minix/rt.h>

int main(int argc, char *argv[])
{
    int period;
    int calctime;
    int i, j, cycles;
    
    if (argc != 4) {
        printf("Wrong number of arguments!\n");
        printf("Usage: ./edf <period> <calctime> <cycles>\n");
        return -1;
    }
        
    period = atoi(argv[1]);
    calctime = atoi(argv[2]);
    cycles = atoi(argv[3]);
    
    rt_set_edf(period, calctime);    
    
    while(1) {
        for (i=0;i<cycles;i++) {
            for (j=0;j<1000000;j++);
        }
        rt_nextperiod();
    }
    
    return 0;
}
