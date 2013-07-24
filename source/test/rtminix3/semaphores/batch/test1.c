/* Test 1
 *
 * Testing the creation of a mutex semaphore under normal conditions
 */

#include "test.h"

#define TESTNR 1

main(void)
{
    sem_t m1;
    
    /* try to create semaphore */
    if (sem_m_create(&m1) != OK) {
        /* creation failed */
        return FAILED;
    } else {
        /* creation succesful */

        /* delete sem */
        if(sem_delete(m1) != OK) {
            DEBUGMSG(TESTNR, "Deleting sem m1 failed");
            return FATAL_FAILURE;
        }   
        return OK;
    }
}   
