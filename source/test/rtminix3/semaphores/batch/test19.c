/* Test 19
 *
 * Testing sem_give of taken mutex with wrong user
 */  

#include "test.h"

#define TESTNR 19

int main(void)
{
    sem_t m1; 
    int pid;
        int result;
    int status; 
    /* create mutex */  
    if (sem_m_create(&m1) != OK) {
        DEBUGMSG(TESTNR, "sem_m_create(&m1) != OK");
        return FAILED;
    }

    /* take mutex */
    if (sem_take(m1, NO_WAIT) != OK) {
        DEBUGMSG(TESTNR, "sem_take(m1, NO_WAIT) != OK");

        if (sem_delete(m1) != OK) {
            DEBUGMSG(TESTNR, "sem_delete(m1) != OK");
            return FATAL_FAILURE;
        }

        return FAILED;  
    }   

    if (pid = fork() != 0) {
        /* parent */
        
        /* wait till child exits and get exit code */
        result = waitpid(-1, &status, 0);
                
        if (WEXITSTATUS(status) != SEM_INVALID_MUTEX_GIVE) {
            DEBUGMSG(TESTNR, "WEXITSTATUS(status) != SEM_INVALID_MUTEX_GIVE");
            
            /* clean up */  
            if (sem_give(m1) != OK) {
                DEBUGMSG(TESTNR, "sem_give(m1) != OK");
            }   

            if (sem_delete(m1) != OK) {
                DEBUGMSG(TESTNR, "sem_delete(m1) != OK");
                return FATAL_FAILURE;
            }   

            return FAILED;

        }   
        
        /* clean up */
        if (sem_give(m1) != OK) {
            DEBUGMSG(TESTNR, "sem_give(m1) != OK");
        }   
        
        if (sem_delete(m1) != OK) {
            DEBUGMSG(TESTNR, "sem_delete(m1) != OK");
            return FATAL_FAILURE;
        }   
        
        /* test passed */
        return OK;
    } else {
        /* child */
        sleep(1);
        result = sem_give(m1);
            
        return result;
    }

    return OK;  
}
