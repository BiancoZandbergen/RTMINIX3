/* The library function implemented in this file:
 *   sem_take
 *
 * Function description:
 *   Take a semaphore.
 * 
 * The parameters for this library function are:
 *   handler:       the semaphore handler
 *   block:         if block is WAIT_FOREVER and the sem
 *                  is not available the process will block
 *                  until it is available. If block is NO_WAIT
 *                  the process will not be blocked. Instead if 
 *                  a semaphore is not available SEM_IN_USE will
 *                  be returned.
 *
 * Return value:
 *   Returns OK (0) if the operation succeeded.
 *   If the return value is not OK an error code
 *   is returned. Check <minix/sem.h> for error codes.
 */
#include <lib.h>
#include <minix/sem.h>

int sem_take(sem_t handler, int block)
{
  message m; /* message we use for the system call */
    
  m.SEM_F_HANDLER = handler; /* set the semaphore handler */
  m.SEM_F_BLOCK = block; /* set the block type */
  
  /* Do the system call and return the result.
   * If the semaphore is not available and block is WAIT_FOREVER
   * it will return when it is unblocked.
   */
  return (_syscall(SS, SEM_TAKE, &m));    
}    

