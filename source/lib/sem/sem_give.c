/* The library function implemented in this file:
 *   sem_give
 *
 * Function description:
 *   This function gives a semaphore free
 * 
 * The parameters for this library function are:
 *   handler:       the semaphore handler
 *
 * Return value:
 *   Returns OK (0) if the operation succeeded.
 *   If the return value is not OK an error code
 *   is returned. Check <minix/sem.h> for error codes.
 */
#include <lib.h>
#include <minix/sem.h>

int sem_give(sem_t handler)
{
  message m; /* message used for the system call */
    
  m.SEM_F_HANDLER = handler; /* Set the semaphore handler */
  
  /* do the system call and return the result */
  return (_syscall(SS, SEM_GIVE, &m));
    
}    

