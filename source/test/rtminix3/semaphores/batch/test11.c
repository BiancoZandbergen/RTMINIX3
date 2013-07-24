/* Test 11
 *
 * Testing non-blocking sem_take with counting sem under normal conditions
 */  

#include "test.h"

#define TESTNR 11

main(void)
{
    sem_t c1;
    int i;
    
    /* creating counting sem with value 3 and size 3 */
    if (sem_c_create(&c1, 3, 3) != OK) {
        DEBUGMSG(TESTNR, "sem_c_create(&c, 3, 3) != OK");
        return FAILED;
    }   

    /* Doing three takes. All should return OK */ 
    for (i=0; i<3; i++) {
        if (sem_take(c1, NO_WAIT) != OK) {
            DEBUGMSG(TESTNR, "sem_take(c1, NO_WAIT) != OK");
            
            /* clean up */
            if (sem_delete(c1) != OK) {
                DEBUGMSG(TESTNR, "sem_delete(c1) != OK");
                return FATAL_FAILURE;
            }   
            return FAILED;
        }   
    }   

    /* doing another take. should return SEM_IN_USE */
    if (sem_take(c1, NO_WAIT) != SEM_IN_USE) {
        DEBUGMSG(TESTNR, "sem_take(c1, NO_WAIT) != SEM_IN_USE");
        
        /* clean up. first make sure that value == size */ 
        for (i=0; i<3; i++) {
            if (sem_give(c1) != OK) {
                   DEBUGMSG(TESTNR, "sem_give(c1) != OK");
            }                  
        }   

        /* delete sem c1 */
        if (sem_delete(c1) != OK) {
            DEBUGMSG(TESTNR, "sem_delete(c1) != OK");
            return FATAL_FAILURE;
        }

        return FAILED;  
    }

    /* clean up. first make sure that value == size */  
    for (i=0; i<3; i++) {
        if (sem_give(c1) != OK) {
            DEBUGMSG(TESTNR, "sem_give(c1) != OK");
        }   
    }
    
    /* delete sem c1 */
    if (sem_delete(c1) != OK) {
        DEBUGMSG(TESTNR, "sem_delete(c1) != OK");
        return FATAL_FAILURE;   
    }   
    
    /* test passed */
    return OK;
}
