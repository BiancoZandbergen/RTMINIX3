/* Dining Philosophers implementation for
 * the semaphore server.
 *
 * It uses a counting semaphore that makes sure
 * that only N-1 philosophers may be in the room.
 * Furthermore a philosopher will try to take the left
 * fork first and after it got the left fork it will
 * try to get the right fork.
 *
 *  Changes:
 *    15 jun 2009   initial release (Bianco Zandbergen) 
 */
#include <stdio.h>
#include <unistd.h>
#include <lib.h>
#include <minix/sem.h>

#define N 6 
#define LEFT_FORK(X) (X+N-1)%N
#define RIGHT_FORK(X) (X)

sem_t waiter; /* the counting semaphore */
sem_t forks[N]; 

void philosopher(int i);
void display_forkstate(int nr);

int main(void) 
{
    int i, result;
    /* create mutex */
    if (sem_c_create(&waiter, (N-1), (N-1)) != OK) printf("Creating mutex failed!\n");
    
    /* create fork semaphores */
    for (i=0;i<N;i++) {
        if (sem_m_create(&forks[i]) != 0) printf("Creating mutex failed\n");
    }

    /* create the philosophers.
     * The philosophers will execute the philosopher() function
     */
    for (i=0;i<N;i++) {
        result = fork();

        if (result == 0) {
            philosopher(i);
        }
    }
    
    while(TRUE) { sleep(1); }

    return -1;
}


void philosopher(int i)
{

    int got_forks;
    int result;
    int j;

    while (TRUE) {
        /* thinking */
        printf("P%d thinking...\n",i);
        fflush(stdout);
    
        sleep(/*(i%3)+*/1);

        /* hungry */
        printf("P%d hungry...\n",i);
        fflush(stdout);
        
        /* get in and get forks */
        sem_take(waiter, WAIT_FOREVER);

        printf("P%d sits down...\n", i);
        
        sem_take(forks[LEFT_FORK(i)], WAIT_FOREVER);
        sem_take(forks[RIGHT_FORK(i)], WAIT_FOREVER);
        
        /* eating */
        printf("P%d eating...\n",i);
        fflush(stdout); 

        /* display_forkstate(i); */
        sleep(/*(i%3)+*/1); 

        /* return forks */
        if (sem_give(forks[LEFT_FORK(i)]) != OK) printf("Cannot give sem free");
        if (sem_give(forks[RIGHT_FORK(i)]) != OK) printf("Cannot give sem free");
        
        /* leave room */
        if (sem_give(waiter) != OK) printf("Cannot give sem free");
                
        
        printf("P%d returned forks\n",i);
            fflush(stdout); 
        /* display_forkstate(i); */ 
     }
}   

void display_forkstate(int nr) {
    int forkstate[N];
    int i, result, value;

    for (i=0;i<N;i++) {
        result = sem_value(forks[i], &value);
        if (result != 0) printf("sem_value failed!\n");
        forkstate[i] = value;
    }
    
    printf("P%d forkstate:  [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] \n",nr,forkstate[0], 
            forkstate[1], forkstate[2], forkstate[3], forkstate[4], forkstate[5]);
    fflush(stdout);
}   

