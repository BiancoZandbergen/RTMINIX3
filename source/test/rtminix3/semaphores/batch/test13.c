/* Test 13
 *
 * Testing sem_give with binary sem under normal conditions 
 */  

#include "test.h"

#define TESTNR 13

main(void)
{
    sem_t b1;
    
    /* create binary sem */
    if (sem_b_create(&b1, 0) != OK) {
        DEBUGMSG(TESTNR, "sem_b_create(&b1, 0) != OK");
        return FAILED;
    }   

    /* give sem */
    if (sem_give(b1) != OK) {
        DEBUGMSG(TESTNR, "sem_give(b1) != OK");

        /* clean up */
        if (sem_delete(b1) != OK) {
            DEBUGMSG(TESTNR, "sem_delete(b1) != OK");
            return FATAL_FAILURE;
        }   
        
        return FAILED;
    }

    /* clean up */
    if (sem_delete(b1) != OK) {
        DEBUGMSG(TESTNR, "sem_delete(b1) != OK");
        return FATAL_FAILURE;
    }   
    
    /* test passed */
    return OK;  
}
