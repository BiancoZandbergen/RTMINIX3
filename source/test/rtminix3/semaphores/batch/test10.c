/* Test 9
 *
 * Testing sem_take with binary semaphore under normal conditions with NO_WAIT
 */  

#include "test.h"

#define TESTNR 10

main(void)
{
    sem_t b1;
    sem_t b2;   
        
    /* create binary sem with value 1 */
    if (sem_b_create(&b1, 1) != OK) {
        DEBUGMSG(TESTNR, "sem_b_create(&b1, 1) != OK");
        return FAILED;
    }   
    
    /* create binary sem with value 0 */
    if (sem_b_create(&b2, 0) != OK) {
        DEBUGMSG(TESTNR, "sem_b_create(&b2, 0) != OK");
        
        /* clean up sem b1 */
        if (sem_delete(b1) != OK) {
            DEBUGMSG(TESTNR, "sem_delete(b1) != OK");
            return FATAL_FAILURE;
        }
        return FAILED;
    }   
    
    /* do a non-blocking sem_take on sem b1. Should return OK */
    if (sem_take(b1, NO_WAIT) != OK) {
        DEBUGMSG(TESTNR, "sem_take(b1, NO_WAIT) != OK");
        
        /* clean up, delete sem b1 */
        if (sem_delete(b1) != OK) {
            DEBUGMSG(TESTNR, "sem_delete(b1) != OK");
            return FATAL_FAILURE;
        }
        
        /* make sure sem b2 has value 1 */
        if (sem_give(b2) != OK) {
            DEBUGMSG(TESTNR, "sem_give(b2) != OK");
        }

        /* delete sem b2 */ 
        if (sem_delete(b2) != OK) {
            DEBUGMSG(TESTNR, "sem_delete(b2) != OK");
            return FATAL_FAILURE;   
        }
        
        return FAILED;
    }

    /* do another non-blocking sem_take on sem b1. Should return SEM_IN_USE */
    if (sem_take(b1, NO_WAIT) != SEM_IN_USE) {
        DEBUGMSG(TESTNR, "sem_take(b1, NO_WAIT) != SEM_IN_USE");
        
        /* clean up */
        /* first make sure that m1 and m2  has value 1 */
        if (sem_give(b1) != OK || sem_give(b2) != OK) {
            DEBUGMSG(TESTNR, "sem_give(b1) != OK || sem_give(b2) != OK");
        }   
        
        /* delete sem b1 and b2 */ 
        if (sem_delete(b1) != OK || sem_delete(b2) != OK) {
            DEBUGMSG(TESTNR, "sem_delete(b1) != OK || sem_delete(b2) != OK");
            return FATAL_FAILURE;
        }   
        
        return FAILED;
    }

    /* do an non-blocking sem_take on sem b2. Should return SEM_IN_USE */
    if (sem_take(b2, NO_WAIT) != SEM_IN_USE) {
        DEBUGMSG(TESTNR, "sem_take(b2, NO_WAIT) != SEM_IN_USE");
        
        /* clean up */
        /* first make sure that m1 and m2  has value 1 */
        if (sem_give(b1) != OK || sem_give(b2) != OK) {
            DEBUGMSG(TESTNR, "sem_give(b1) != OK || sem_give(b2) != OK");
        }   
        
        /* delete sem b1 and b2 */ 
        if (sem_delete(b1) != OK || sem_delete(b2) != OK) {
            DEBUGMSG(TESTNR, "sem_delete(b1) != OK || sem_delete(b2) != OK");
            return FATAL_FAILURE;
        }   
        
        return FAILED;
    }
    
    /* clean up */
    /* first make sure that sem m1 and m2 has value 1 */
    if (sem_give(b1) != OK || sem_give(b2) != OK) {
        printf("Test TESTNR: sem_give(b1) or sem_give(b2) failed\n");
    }

    if(sem_delete(b1) != OK || sem_delete(b2) != OK) {
        DEBUGMSG(TESTNR, "sem_delete(b1) != OK || sem_delete(b2) != OK");
        return FATAL_FAILURE;
    }   

    return OK;
}

