/* Test 3
 *
 * Testing the creation of counting semaphores under normal conditions
 */

#include "test.h"

#define TESTNR 3

main(void)
{
    sem_t c1;
    sem_t c2;
    sem_t c3;
    int i;
    
    /* try to create counting semaphore with value 0 and size 6 */
    if (sem_c_create(&c1, 0, 6) != OK) {
        /* Test failed */
        DEBUGMSG(TESTNR, "sem_c_create(&c1, 0, 6) != OK");
        return FAILED;
    }
        /* try to create counting semaphore with value 3 and size 6 */
    else if (sem_c_create(&c2, 3, 6) != OK) {
        /* Test failed */
        DEBUGMSG(TESTNR, "sem_c_create(&c2, 3, 6) != OK");
        
        /* delete sem c1 that has been created succesful */
        /* First make sure that the value equals the size of the semaphore */
                for (i=0;i<6;i++) {
                        if (sem_give(c1) != OK) {
                DEBUGMSG(TESTNR, "sem_give(c1) != OK");
            }   
                }
        
        if (sem_delete(c1) != OK) {
            DEBUGMSG(TESTNR, "sem_delete(c1) != OK");
            return FATAL_FAILURE;
        }   
        
        return FAILED;
    } 
    /* try to create counting semaphore with value 6 and size 6 */
    else if (sem_c_create(&c3, 6, 6) != OK) {
        /* Test failed */
        DEBUGMSG(TESTNR, "sem_c_create(&c3, 6, 6) != OK)");
        
        /* Deleting the two sems that are created succesful */
        /* First make sure that the value equals the size of the semaphores */
                for (i=0;i<6;i++) {
                        if (sem_give(c1) != OK) {
                DEBUGMSG(TESTNR, "sem_give(c1) != OK");
            }   
                }                       
        
                for (i=0;i<3;i++) {
                        if (sem_give(c2) != OK) {
                DEBUGMSG(TESTNR, "sem_give(c2) != OK");
            }   
                }

        if (sem_delete(c1) != OK) {
            DEBUGMSG(TESTNR, "sem_delete(c1) != OK");
            return FATAL_FAILURE;
        }
        
        if (sem_delete(c2) != OK) {
            DEBUGMSG(TESTNR, "sem_delete(c2) != OK");
            return FATAL_FAILURE;
        }
        return FAILED;
    } else {
        /* Test passed */
        
        /* Deleting the three sems */
        /* First make sure that the value equals the size of the semaphores */
        for (i=0;i<6;i++) {
            if (sem_give(c1) != OK) {
                DEBUGMSG(TESTNR, "sem_give(c1) != OK");
            }   
        }       
        for (i=0;i<3;i++) {
            if (sem_give(c2) != OK) {
                DEBUGMSG(TESTNR, "sem_give(c2) != OK");
            }   
        }
        
        if (sem_delete(c1) != OK) {
            DEBUGMSG(TESTNR, "sem_delete(c1) != OK");
            return FATAL_FAILURE;
        }   
        if (sem_delete(c2) != OK) {
            DEBUGMSG(TESTNR, "sem_delete(c2) != OK");
            return FATAL_FAILURE;
        }   
        if (sem_delete(c3) != OK) {
            DEBUGMSG(TESTNR, "sem_delete(c3) != OK");
            return FATAL_FAILURE;
        }   

        return OK;  
     }      
}   
