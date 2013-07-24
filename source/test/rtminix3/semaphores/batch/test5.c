/* Test 5
 *
 * Testing the creation of a binary semaphore with invalid value parameters 
 */

#include "test.h"

#define TESTNR 5

main(void)
{
    sem_t b1;
    sem_t b2;
    int result;
    
    /* try to create binary semaphore with value 2 */
    if (result = sem_b_create(&b1, 2) != SEM_INVALID_VALUE) {
        if (result == OK) {
            if (sem_delete(b1) != OK) {
                DEBUGMSG(TESTNR, "sem_delete(b1) != OK");
                return FATAL_FAILURE;
            }   
        }   
        return FAILED;
    } 
    
    /* try to create binary semaphore with value -1 */
    if (result = sem_b_create(&b2, -1) != SEM_INVALID_VALUE) {
        if (result == OK) {
            if (sem_delete(b2) != OK) {
                DEBUGMSG(TESTNR, "sem_delete(b2) != OK");
                return FATAL_FAILURE;
            }   
        }   
        return FAILED;
    } 
    
    return OK;
}   

