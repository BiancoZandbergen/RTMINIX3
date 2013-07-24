/* The library function implemented in this file:
 *   sem_c_create
 *
 * Function description:
 *   This function creates a new counting semaphore.
 * 
 * The parameters for this library function are:
 *   handler:       pointer to handler we want to create
 *   value:         initial value (can't be lager than size)
 *   size:          size of the counting semaphore
 *
 * Return value:
 *   Returns OK (0) if the operation succeeded.
 *   If the return value is not OK an error code
 *   is returned. Check <minix/sem.h> for error codes.
 */
#include <lib.h>
#include <minix/sem.h>

int sem_c_create(sem_t *handler, int value, int size)
{
  message m; /* message we use for the system call */
  int result; /* we will have to save the result of the system call */
    
  m.SEM_F_TYPE = SEM_COUNTING; /* we want to create a counting sem */
  m.SEM_F_VALUE = value; /* set the value in the message */
  m.SEM_F_SIZE = size; /* set the size in the message */

  /* do the system call and save the result */
  result = _syscall(SS, SEM_CREATE, &m);

  /* Set the semaphore handler in the user program.
   * The handler is only valid if the result was OK.
   */
  *handler = m.SEM_F_HANDLER;
    
  return (result);
}   

