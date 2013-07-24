/* Test 2
 *
 * Testing the creation of binary semaphore under normal conditions
 */

#include "test.h"

#define TESTNR 2

main(void)
{
    sem_t b1;
    sem_t b2;
    
    /* try to create binary semaphore with a start value of 0 and 1 */
    if (sem_b_create(&b1, 0) != OK) {
        /* Test failed */
        DEBUGMSG(TESTNR, "sem_b_create(&b1, 0) != OK");
        return FAILED;
    } else if (sem_b_create(&b2, 1) != OK) {
        /* Test failed */
        DEBUGMSG(TESTNR, "sem_b_create(&b2, 1) != OK");
        
        /* delete sem bin1 that has been created succesful */
        if (sem_delete(b1) != OK) {
            DEBUGMSG(TESTNR, "sem_delete(b1) != OK");
            return FATAL_FAILURE;
        }   
        return FAILED;
    } else {
        /* Test passed */
        
        /* Deleting the two sems */
        /* first make sure b1 has value 1 */
        if (sem_give(b1) != OK) {
            DEBUGMSG(TESTNR, "sem_give(b1) != OK");
        }           
        if (sem_delete(b1) != OK) {
            DEBUGMSG(TESTNR, "sem_delete(b1) != OK");
            return FATAL_FAILURE;
        }   
        if (sem_delete(b2) != OK) {
            DEBUGMSG(TESTNR, "sem_delete(b2) != OK");
            return FATAL_FAILURE;
        }   

        return OK;  
     }      
}   
