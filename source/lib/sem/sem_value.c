/* The library function implemented in this file:
 *   sem_value
 *
 * Function description:
 *   Returns the value of a semaphore
 * 
 * The parameters for this library function are:
 *   handler:       the semaphore handler
 *   value:         pointer to store the returned value
 *
 * Return value:
 *   Returns OK (0) if the operation succeeded.
 *   If the return value is not OK the error code
 *   is returned. Check <minix/sem.h> for error codes.
 */
#include <lib.h>
#include <minix/sem.h>

int sem_value(sem_t handler, int *value)
{
  message m; /* message we use for the system call */
  int result; /* we have to save the result of the system call */
  
  m.SEM_F_HANDLER = handler; /* set the semaphore handler */

  /* do the system call and save the result */
  result = _syscall(SS, SEM_VALUE, &m);

  /* Set the value in the user program */
  *value = m.SEM_F_VALUE;  

  return result;
}

