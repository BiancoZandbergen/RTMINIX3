/* Test 8
 *
 * Testing sem_take with invalid semaphore handler
 */  

#include "test.h"

#define TESTNR 8

main(void)
{
    sem_t m1; /* uninitialized sem handler should be invalid */
                 
    if (sem_take(m1, NO_WAIT) != SEM_INVALID_HANDLER) {
        return FAILED;
    } else {
        return OK;
    }   
}
