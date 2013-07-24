/* Test 9
 *
 * Testing sem_take with mutex under normal conditions with NO_WAIT
 */  

#include "test.h"

#define TESTNR 9

main(void)
{
    sem_t m1;
    
    /* create sem */
    if (sem_m_create(&m1) != OK) {
        DEBUGMSG(TESTNR, "sem_m_create(&m1) != OK");
        return FAILED;
    }   
    
    /* do a non-blocking sem_take. Should return OK */
    if (sem_take(m1, NO_WAIT) != OK) {
        DEBUGMSG(TESTNR, "sem_take(m1, NO_WAIT) != OK");
        
        /* clean up */
        if (sem_delete(m1) != OK) {
            DEBUGMSG(TESTNR, "sem_delete(m1) != OK");
            return FATAL_FAILURE;
        }   
        
        return FAILED;
    }

    /* do another non-blocking sem_take. Should return SEM_IN_USE */
    if (sem_take(m1, NO_WAIT) != SEM_IN_USE) {
        DEBUGMSG(TESTNR, "sem_take(m1, NO_WAIT) != SEM_IN_USE");
        
        /* clean up */
        /* first make sure that m1 has value 1 */
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
    /* first make sure that m1 has value 1 */
    if (sem_give(m1) != OK) {
        DEBUGMSG(TESTNR, "sem_give(m1) != OK");
    }
    
    if(sem_delete(m1) != OK) {
        DEBUGMSG(TESTNR, "sem_delete(m1) != OK");
        return FATAL_FAILURE;
    }   

    return OK;
}



