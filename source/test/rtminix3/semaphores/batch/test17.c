/* Test 17
 *
 * Testing sem_give with binary sem while sem is not taken  
 */  

#include "test.h"

#define TESTNR 17

int main(void)
{
    sem_t b1; 
    
    /* create mutex */
    if (sem_b_create(&b1, 1) != OK) {
        DEBUGMSG(TESTNR, "sem_b_create(&b1, 1) != OK");
        return FAILED;
    }   

    /* do a sem_give while sem is not taken */
    if (sem_give(b1) != SEM_ALREADY_FREE) {
        DEBUGMSG(TESTNR, "sem_give(b1) != SEM_ALREADY_FREE");
        
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
