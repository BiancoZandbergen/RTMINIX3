/* Test 15
 *
 * Testing sem_give with invalid semaphore handler
 */  

#include "test.h"

#define TESTNR 15

main(void)
{
    sem_t b1; /* uninitialized sem handler should be invalid */
    
    if (sem_give(b1) != SEM_INVALID_HANDLER) {
        return FAILED;
    } else {
        return OK;
    }   
}
