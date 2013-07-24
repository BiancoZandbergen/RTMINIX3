/* Test 6
 *
 * Testing the creation of a counting semaphore with invalid value parameter 
 */

#include "test.h"

#define TESTNR 6

main(void)
{
    sem_t c1;
    sem_t c2;
    int result;
    
    /* try to create counting semaphore with value 7, size 6 */
    if (result = sem_c_create(&c1, 7, 6) != SEM_INVALID_VALUE) {
        if (result == OK) {
            if (sem_delete(c1) != OK) {
                DEBUGMSG(TESTNR, "sem_delete(c1) != OK");
                return FATAL_FAILURE;
            }   
        }   
        return FAILED;
    } 
    
    /* try to create counting semaphore with value -1, size 6 */
    if (result = sem_c_create(&c2, -1, 6) != SEM_INVALID_VALUE) {
        if (result == OK) {
            if (sem_delete(c2) != OK) {
                DEBUGMSG(TESTNR, "sem_delete(c2) != OK");
                return FATAL_FAILURE;
            }   
        }   
        return FAILED;
    } 
    
    return OK;
}   
