/* Test 4
 *
 * Testing the creation of a semaphore with invalid type  
 * */

#include "test.h"

#define TESTNR 4

main(void)
{
    sem_t sem;
    message m;
    int result;
    
    /* trying to create sem with type 4 */
    m.SEM_F_TYPE = 4;
    result = _syscall(SS, SEM_CREATE, &m);

    if (result != SEM_INVALID_TYPE) {
        if (result == OK) {
            if (sem_delete(m.SEM_F_HANDLER) != OK) {
                DEBUGMSG(TESTNR, "sem_delete(m.SEM_F_HANDLER) != OK");
                return FATAL_FAILURE;
            }   
        }   
        return FAILED;
    }   

    /* trying to create sem with type 0 */
    m.SEM_F_TYPE = 0;
    result = _syscall(SS, SEM_CREATE, &m);
    
    if (result != SEM_INVALID_TYPE) {
        if (result == OK) {
            if (sem_delete(m.SEM_F_HANDLER) != OK) {
                DEBUGMSG(TESTNR, "sem_delete(m.SEM_F_HANDLER) != OK");
                return FATAL_FAILURE;
            }   
        }   
        return FAILED;
    }   

    /* trying to create sem with type -1 */
    m.SEM_F_TYPE = -1;
    result = _syscall(SS, SEM_CREATE, &m);
    
    if (result != SEM_INVALID_TYPE) {
        if (result == OK) {
            if (sem_delete(m.SEM_F_HANDLER) != OK) {
                DEBUGMSG(TESTNR, "sem_delete(m.SEM_F_HANDLER) != OK");
                return FATAL_FAILURE;
            }   
        }   
        return FAILED;
    }   
    
    return OK;
}   

