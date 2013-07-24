/* Test 16
 *
 * Testing sem_give with mutex while sem is not taken  
 */  

#include "test.h"

#define TESTNR 16

int main(void)
{
    sem_t m1; 
    int result; 
    /* create mutex */
    if (sem_m_create(&m1) != OK) {
        DEBUGMSG(TESTNR, "sem_m_create(&m1) != OK");
        return FAILED;
    }   
    
    /* do a sem_give while sem is not taken */
    if (result=sem_give(m1) != SEM_ALREADY_FREE) {
        DEBUGMSG(TESTNR, "sem_give(m1) != SEM_ALREADY_FREE");
        printf("Result: %d\n", result);

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
