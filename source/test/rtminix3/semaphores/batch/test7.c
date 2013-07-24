/* Test 7
 *
 * Testing the creation of a counting semaphore with invalid size parameter 
 */

#include "test.h"

#define TESTNR 7

main(void)
{
    sem_t c1;
    int result;
    
    /* try to create counting semaphore with value 0, size 0 */
    if (result = sem_c_create(&c1, 0, 0) != SEM_INVALID_SIZE) {
        if (result == OK) {
            if (sem_delete(c1) != OK) {
                DEBUGMSG(TESTNR, "sem_delete(c1) != OK");
                return FATAL_FAILURE;
            }   
        }   
        return FAILED;
    } 
    
    return OK;
}   
