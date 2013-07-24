/* The library function implemented in this file:
 *   sem_b_create
 *
 * Function description:
 *   This function creates a new binary semaphore.
 * 
 * The parameters for this library function are:
 *   handler:       pointer to handler we want to create
 *   value:         initial value (can be 0 or 1)
 *
 * Return value:
 *   Returns OK (0) if the operation succeeded.
 *   If the return value is not OK an error code
 *   is returned. Check <minix/sem.h> for error codes.
 */
#include <lib.h>
#include <minix/sem.h>

int sem_b_create(sem_t *handler, int value)
{
  message m; /* message we use for the system call */
  int result; /* we will have to save the result of the system call */
    
  m.SEM_F_TYPE = SEM_BINARY; /* we want to create a binary sem */
  m.SEM_F_VALUE = value; /* the initial value */
  
  /* do the system call and save the result */
  result = _syscall(SS, SEM_CREATE, &m); 

  /* Set the semaphore handler in the user program.
   * The handler is only valid of the result was OK.
   */
  *handler = m.SEM_F_HANDLER;
    
  return (result);
}

