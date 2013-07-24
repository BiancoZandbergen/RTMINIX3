/* Test 14
 *
 * Testing sem_give with counting sem under normal conditions 
 */  

#include "test.h"

#define TESTNR 14

main(void)
{
    sem_t c1;
    
    /* create counting sem */
    if (sem_c_create(&c1, 4, 5) != OK) {
        DEBUGMSG(TESTNR, "sem_c_create(&c1, 4, 5) != OK");
        return FAILED;
    }   

    /* give sem */
    if (sem_give(c1) != OK) {
        DEBUGMSG(TESTNR, "sem_give(c1) != OK");

        /* clean up */
        if (sem_delete(c1) != OK) {
            DEBUGMSG(TESTNR, "sem_delete(c1) != OK");
            return FATAL_FAILURE;
        }   
        
        return FAILED;
    }

    /* clean up */
    if (sem_delete(c1) != OK) {
        DEBUGMSG(TESTNR, "sem_delete(c1) != OK");
        return FATAL_FAILURE;
    }   
    
    /* test passed */
    return OK;  
}
