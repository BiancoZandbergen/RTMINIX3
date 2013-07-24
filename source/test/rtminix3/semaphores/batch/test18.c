/* Test 18
 *
 * Testing sem_give with counting sem while sem is not taken  
 */  

#include "test.h"

#define TESTNR 18

int main(void)
{
    sem_t c1; 
    
    /* create mutex */
    if (sem_c_create(&c1, 5, 5) != OK) {
        DEBUGMSG(TESTNR, "sem_c_create(&c1, 5, 5) != OK");
        return FAILED;
    }   

    /* do a sem_give while sem is not taken */
    if (sem_give(c1) != SEM_ALREADY_FREE) {
        DEBUGMSG(TESTNR, "sem_give(c1) != SEM_ALREADY_FREE");
        
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
