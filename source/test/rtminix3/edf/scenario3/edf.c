#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <minix/rt.h>

int main(int argc, char *argv[])
{
    int period;
    int calctime;
    
    if (argc != 3) {
        printf("Wrong number of arguments!\n");
        printf("Usage: ./edf <period> <calctime>\n");
        return -1;
    }
        
    period = atoi(argv[1]);
    calctime = atoi(argv[2]);
   
    rt_set_edf(period, calctime);    
    
    while(1);
    
    return 0;
}
