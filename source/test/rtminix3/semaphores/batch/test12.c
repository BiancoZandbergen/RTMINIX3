/* Test 12
 *
 * Testing sem_give with mutex under normal conditions 
 */  

#include "test.h"

#define TESTNR 12

main(void)
{
    sem_t m1;
    
    /* create mutex */
    if (sem_m_create(&m1) != OK) {
        DEBUGMSG(TESTNR, "sem_m_create(&m1) != OK");
        return FAILED;
    }   

    /* take sem */
    if (sem_take(m1, NO_WAIT) != OK) {
        DEBUGMSG(TESTNR, "sem_take(m1, NO_WAIT) != OK");
    }   

    /* give sem */
    if (sem_give(m1) != OK) {
        DEBUGMSG(TESTNR, "sem_give(m1) != OK");

        /* clean up */
        if (sem_delete(m1) != OK) {
            DEBUGMSG(TESTNR, "sem_delete(m1) != OK");
            return FATAL_FAILURE;
        }   
        
        return FAILED;
    }

    /* clean up */
    if (sem_delete(m1) != OK) {
        DEBUGMSG(TESTNR, "sem_delete(m1) != OK");
        return FATAL_FAILURE;
    }
    
    /* test passed */
    return OK;  
}
