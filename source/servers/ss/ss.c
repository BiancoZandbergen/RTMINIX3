/* This file contains the implementation of the Semaphore Server.
 * It contains the following functions:
 *   main: The main program
 *   init: initialize the server
 *   sem_create: create a new semaphore
 *   sem_take: take a semaphore
 *   sem_give: give a semaphore free
 *   sem_delete: delete a semaphore
 *   sem_flush: unblock all blocked processes
 *   sem_value: get value of semaphore
 *   procexit: used by pm to tell the server that a process has exited
 *
 * Changes:
 *   June 14, 2009  initial release (Bianco Zandbergen)
 */
#include <stdio.h>
#include <lib.h>
#include <unistd.h>
#include <stdlib.h>
#include <timers.h>
#include <minix/syslib.h>
#include "../../kernel/proc.h"
#include "ss.h"

/* user processes use virtual sem handlers
 * SS internal uses real sem handlers. We do this because
 * real sem handlers are the same as the array indices in semtable.
 * These start at 0 and an uninitialized sem handler also has the value of
 * 0. To prevend the use of uninitialized sem handlers we use virtual sem handlers
 * outside the SS.
 * VIR_SEM_HANDLER converts a real handler to a virtual handler.
 * REAL_SEM_HANDLER converts a virtual handler to a real handler.
 */
#define VIR_SEM_HANDLER(real) (real+1)
#define REAL_SEM_HANDLER(vir) (vir-1)

/* checks is a sem handler is valid, real sem handler is used as arg */
#define VALID_SEM(X) ((X < NR_SEMS) && (semtable[X].used == 1))

message m;

int main(void) {

  int caller;

  /* reset values */
  init();
    
  while(1) {
      receive(ANY, &m); /* get work */
      caller = m.m_source;
        
      /* Invoke the right function depending on the message type.
       * Depending on the function and return value it will send a reply
       * back to the caller process.
       */        
      switch(m.m_type) {
          case SEM_CREATE:
              m.m_type = sem_create(m.SEM_F_TYPE, m.SEM_F_VALUE,  m.SEM_F_SIZE);
              if(send(caller, &m) != OK) printf("ss: Sending back failed!\n");
              break;
          case SEM_TAKE:
              m.m_type = sem_take(REAL_SEM_HANDLER(m.SEM_F_HANDLER), m.SEM_F_BLOCK);
              if (m.m_type == OK || m.m_type == SEM_INVALID_HANDLER || m.m_type == SEM_INVALID_BLOCK ||
                      (m.SEM_F_BLOCK == NO_WAIT && m.m_type == SEM_IN_USE)) {
                  /* We only send back if the sem was available or the sem handler was invalid
                   * or the block arg was invalid or the sem was not 
                   * available AND the process does not want to wait.
                   */
                  if(send(caller, &m) != OK) printf("ss: Sending back failed!\n");
              }    
              break;
          case SEM_GIVE:
              m.m_type = sem_give(REAL_SEM_HANDLER(m.SEM_F_HANDLER));
              if(send(caller, &m) != OK) printf("ss: Sending back failed! \n");
              break;
          case SEM_FLUSH:
              m.m_type = sem_flush(REAL_SEM_HANDLER(m.SEM_F_HANDLER));
              if(send(caller, &m) != OK) printf("ss: Sending back failed! \n");
              break;
          case SEM_DELETE:
              m.m_type = sem_delete(REAL_SEM_HANDLER(m.SEM_F_HANDLER));
              if(send(caller, &m) != OK) printf("ss: Sending back failed! \n");
              break;
          case SEM_PROCEXIT:
              #ifdef SEM_DEBUG
              printf("ss: process exited! endpt: %d\n",m.SEM_F_ENDPT);
              #endif
              procexit(m.SEM_F_ENDPT);
              /* we don't have to send back! */
              break;
          case SEM_VALUE:
              m.m_type = sem_value(REAL_SEM_HANDLER(m.SEM_F_HANDLER));
              if(send(caller, &m) != OK) printf("ss: Sending back failed! \n");
              break;
          default:
              m.m_type = (EINVAL);
              if (send(caller, &m) != OK) printf("ss: Sending back failed! \n");    
      }
  }
}

/****************************************
 *      init                            *
 ****************************************/      
void init(void) {

  int i;
  used = 0;

  for(i=0; i<NR_SEMS; i++) {
      semtable[i].used = 0;
      semtable[i].listp = NULL;
  }
}

/****************************************
 *      sem_create                      *
 ****************************************/      
int sem_create(int type, int value, int size)
{
  /* Create a new semaphore */
    
  int i;

  #ifdef SEM_DEBUG
  printf("sem_create type: %d, value: %d, size: %d\n",type,value,size);
  #endif
    
  /* check if type is valid 
   * semtypes: 1=mutex,2=binary,3=counting
   */
  if (type > 3 || type < 1) return SEM_INVALID_TYPE;

  /* All semaphores in use! */
  if (used >= NR_SEMS) return SEM_NO_AVAILABLE;
    
  /* type specific checks */
  if (type == SEM_BINARY) {
      
      /* value must be 0 or 1 */
      if (value != 0 && value != 1) {
          return SEM_INVALID_VALUE;
      } 
  } else if (type == SEM_COUNTING) {
      
      /* value cannot be larger than size, value cannot be negative */
      if (value > size || value < 0) {
          return SEM_INVALID_VALUE;
      } else if (size < 1) {
          /* size must be larger than 1 */
          return SEM_INVALID_SIZE;
      } 
  } 
    
  i = 0;

  /* find unused sem */
  while(semtable[i].used != 0 && i < NR_SEMS) i++;
  if (i == NR_SEMS) return SEM_NO_AVAILABLE;
        
  semtable[i].used = 1;
  semtable[i].sem_type = type;
  semtable[i].listp = NULL; /* no blocked processes in queue */
  semtable[i].owner = m.m_source; /* endpoint nr of the caller process */
  used++;

  /* setting value and size */
  switch (type) {
      case SEM_MUTEX:
          semtable[i].value = 1;
          break;
      case SEM_BINARY:
          semtable[i].value = value;
          break;
      case SEM_COUNTING:
          semtable[i].value = value;
          semtable[i].size = size;
          break;
  }

  #if 0 
  printf("ss: found unused sem: real %d vir: %d\n", i, VIR_SEM_HANDLER(i));
  #endif
  
  /* we return a virtual sem handler to the caller process */
  m.SEM_F_HANDLER = VIR_SEM_HANDLER(i);
  
  return OK;
}

/****************************************
 *      sem_take                        *
 ****************************************/      
int sem_take(int sem_handler, int block)
{
  /* Take a semaphore */
    
  struct sem_proc * sproc;
  struct sem_proc ** xpp;
  struct proc caller_proc;
  int result;
    
  /* check if sem handler is valid */
  if (!VALID_SEM(sem_handler)) return SEM_INVALID_HANDLER;
  
  /* get process structure from caller */
  if (result = sys_getproc(&caller_proc, m.m_source) != OK) {
      printf("ss: sys_getproc failed result: %d\n", result);
  }    
    
  switch (semtable[sem_handler].sem_type) {
      case SEM_MUTEX:
      case SEM_BINARY:
          if (semtable[sem_handler].value == 1) {
              /* sem is available */
              semtable[sem_handler].value = 0;
              semtable[sem_handler].user = m.m_source;
              return OK;
          } else {
              /* sem is not available */
              
              if (block == NO_WAIT) {
                  /* caller doesn't want to wait */
                  return SEM_IN_USE;
                    
              } else if (block == WAIT_FOREVER) {
                        
                  /* caller does want to wait.
                   * Add caller to the list of waiting processes on the sem.
                   */
                  
                  /* create new sem_proc struct */
                  sproc = malloc(sizeof(struct sem_proc));
                  
                  /* set the priority of the sem_proc struct to the 
                   * minix scheduling priority.
                   */
                  sproc->prio = caller_proc.p_priority;
                    
                  /* set the caller endpoint */
                  sproc->endpoint = m.m_source;
                  
                  /* find the right place in the list.
                   * The list is ordened on minix scheduling priority.
                   */
                  xpp = &semtable[sem_handler].listp;
                  while (*xpp != NULL && (*xpp)->prio <= sproc->prio) {
                      xpp = &(*xpp)->next;
                  }
                
                  /* add new sem_proc to the list */
                  sproc->next = *xpp;
                  *xpp = sproc;
              } else {
                  /* invalid block argument specified */
                  return SEM_INVALID_BLOCK;
              }                
          }
          break;
      case SEM_COUNTING:
          if(semtable[sem_handler].value > 0) {
              /* sem is available */
              semtable[sem_handler].value--;
              return OK;
          } else if (semtable[sem_handler].value == 0) {
              /* sem is not available */    
              
              if (block == NO_WAIT) {
                  /* caller does not want to wait */
                  return SEM_IN_USE;
                
              } else if (block = WAIT_FOREVER) {                                        
                    
                  /* caller does want to wait.
                   * Add caller to the list of waiting processes on the sem.
                   */    
                  
                  /* create new sem proc_struct */
                  sproc = malloc(sizeof(struct sem_proc));
                  
                  /* set the priority of the sem_proc struct to the
                   * minix scheduling priority.
                   */
                  sproc->prio = caller_proc.p_priority;
                
                  /* set the caller endpoint */    
                  sproc->endpoint = m.m_source;
                  
                  /* find the right place in the list.
                   * The list is ordened on minix scheduling priority */
                  xpp = &semtable[sem_handler].listp;
                  while (*xpp != NULL && (*xpp)->prio <= sproc->prio) {
                      xpp = &(*xpp)->next;
                  }    
                
                  /* add new sem_proc to the list */
                  sproc->next = *xpp;
                  *xpp = sproc;
              } else {
                  /* invalid block argument specified */
                  return SEM_INVALID_BLOCK;
              }                  
          }
          break;
  }

  /* will be reached if sem is not available and caller should block */
  return -1;
}

/****************************************
 *      sem_give                        *
 ****************************************/      
int sem_give(int sem_handler)
{
  /* Give a semaphore free */
    
  struct sem_proc * sproc;
  message m_out;
  int s;
    
  /* check if handler is valid */
  if (! VALID_SEM(sem_handler)) return SEM_INVALID_HANDLER;   
    
  switch(semtable[sem_handler].sem_type) {
      case SEM_MUTEX:
            
          /* a semaphore must be taken in order to give is free.
           * We do this check again at the SEM_BINARY case.
           * It is done here because this check must be done BEFORE
           * the test below. (A sem that is not taken does has have a valid user)
           */
          if (semtable[sem_handler].value > 0) {
              return SEM_ALREADY_FREE;
          }    
            
          /* mutex has one extra condition compared to binary:
           * a give may only be done if the same process
           * took the semaphore.
           */
          if (semtable[sem_handler].user != m.m_source) {
              return SEM_INVALID_MUTEX_GIVE;
          }
          /* do not break! */
      case SEM_BINARY:
          /* a semaphore must be taken in order to give is free */
          if (semtable[sem_handler].value > 0) {
              return SEM_ALREADY_FREE;
          }    
          
          /* give sem free */
          semtable[sem_handler].value = 1;

          /* check for processes in the wait queue blocked
           * on this semaphore. We will have to unblock the next process
           * in the queue. We do this in a while loop because we might need to
           * try multiple times. send() may fail because a process in the queue
           * is not excistant. It may be killed for example. if send() does not
           * fail the code is only executed once.
           */
          while (semtable[sem_handler].listp != NULL) {
                
              /* we save the head of the block queue to sproc before removing it */
              sproc = semtable[sem_handler].listp;
                
              /* remove the head of the queue (sproc) */
              semtable[sem_handler].listp = sproc->next;
                
              /* try to unblock the process */
              if(s=send(sproc->endpoint, &m) != OK) {
                    
                  /* This process is not valid.
                   * Might be killed.
                   * Release memory.
                   */
                  free(sproc);
                  printf("ss: Sending unblock failed!\n");
              } else {
                    
                  /* sem is taken again */
                  semtable[sem_handler].value = 0;
                    
                  /* save endpoint of process that took the sem */
                  semtable[sem_handler].user = sproc->endpoint;   
                    
                  /* release memory */
                  free(sproc);

                  /* unblock successful so stop looping */
                  break;
              }   
          }
          return OK;
          break;
      case SEM_COUNTING:

          /* if value equals size the sem is 'full' and we can't give it free */
          if (semtable[sem_handler].value == semtable[sem_handler].size) {
              return SEM_ALREADY_FREE;
          }    

          /* give sem free */
          semtable[sem_handler].value++;
            
          /* check for processes in the wait queue blocked
           * on this semaphore. We will have to unblock the next process
           * in the queue. We do this in a while loop because we might need to
           * try multiple times. send() may fail because a process in the queue
           * is not excistant. It may be killed for example. if send() does not
           * fail the code is only executed once.
           */
          while (semtable[sem_handler].listp != NULL) {
                
              /* we save the head of the block queue to sproc before removing it */
              sproc = semtable[sem_handler].listp;

              /* remove the head of the block queue */
              semtable[sem_handler].listp = sproc->next;
                
              /* try to unblock the process */
              if(s=send(sproc->endpoint, &m) != OK) {
                    
                  /* This process is not valid.
                   * Might be killed.
                   * Release memory.
                   */
                  free(sproc);
                  printf("ss: Sending unblock failed!\n");
              } else {
                    
                  /* decrease sem (taking it) */                     
                  semtable[sem_handler].value--;
                
                  /* save endpoint of process that took sem */    
                  semtable[sem_handler].user = sproc->endpoint;
                    
                  /* release memory */
                  free(sproc);

                  /* unblock successful so stop looping */
                  break;
              }   
          }
          return OK;
          break;
      default:
          /* invalid semaphore type */
          return SEM_INVALID_TYPE;            
  }
    
  /* never reached */
  return -1;
}

/****************************************
 *      sem_flush                       *
 ****************************************/      
int sem_flush(int handler)
{
  /* unblocks all processes blocked
   * on a binary semaphore.
   * Can be used to synchronize processes.
   */
  struct sem_proc * sproc;
  message m_out;
  m_out.m_type = OK;
   
  /* check if sem handler is valid */
  if (! VALID_SEM(handler)) return SEM_INVALID_HANDLER;

  /* we only allow flush on binary semaphores */
  if (semtable[handler].sem_type != SEM_BINARY) return SEM_INVALID_TYPE;

  /* unblock all processes on the block queue */
  while (semtable[handler].listp != NULL) {
      sproc = semtable[handler].listp; /* get next process from the queue */
        
      /* send a message to the process to unblock it */
      if (send(sproc->endpoint, &m_out) != OK) {
          printf("ss: Sending unblock failed!\n");
      }
        
      semtable[handler].listp = sproc->next; /* remove head from the queue */
      free(sproc); /* release memory */ 
  }

  return OK;
}

/****************************************
 *      sem_delete                      *
 ****************************************/      
int sem_delete(int handler)
{
  /* Delete a semaphore. */

  /* check if sem handler is valid */
  if (! VALID_SEM(handler)) return SEM_INVALID_HANDLER;
  
  switch (semtable[handler].sem_type) {

      case SEM_MUTEX:
      case SEM_BINARY:
          /* A bin/mutex semaphore can only be deleted if it is not taken */
          if (semtable[handler].value == 1) {
              semtable[handler].used = 0; /* release slot */
              used--;
          } else {
              return SEM_IN_USE;
          }
          break;
      case SEM_COUNTING:
          /* A counting semaphore can only be deleted if it is 'full' */
          if (semtable[handler].value == semtable[handler].size) {
              semtable[handler].used = 0; /* release slot */
              used--;
          } else {
              return SEM_IN_USE;
          }
          break;
  }

  return OK;
}
                
/****************************************
 *      sem_procexit                    *
 ****************************************/      
int procexit(int endpoint)
{
  /* Used by the process manager to inform that a process has exited.
   * Deletes all semaphores with the exited process as owner.
   */
  int no_sems;
  int current_sem;

  current_sem = 0;
  no_sems = 0; /* expirimental */

  /* loop through the semaphore table */
  while (/*no_sems < used &&*/ current_sem < NR_SEMS) {
      /* check if semaphore is in use */
      if (semtable[current_sem].used == 1) {
          no_sems++; /* expirimental, not used */
          
          /* check if the exited process is the owner.
           * If so release the semaphore slot.
           */
          if (semtable[current_sem].owner == endpoint) {
              semtable[current_sem].used = 0;
              used--;
              printf("ss: deleted sem %d owned by %d\n",current_sem, endpoint);
                
          }
      }
      current_sem++;
  }
    
  return OK;
}

/****************************************
 *     sem_value                        *
 ****************************************/      
int sem_value(sem_t handler)
{
  /* Returns the value of a semaphore to a user process.
   * May be used for debugging purposes.
   */

  /* check if handler is valid */  
  if (! VALID_SEM(handler)) return SEM_INVALID_HANDLER;

  /* save the value to the message the main loop sends back */
  m.SEM_F_VALUE = semtable[handler].value;
  
  return OK;
}   
