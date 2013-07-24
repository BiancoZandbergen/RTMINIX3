/* Main header file for semaphores.
 * Processes using this functionality should be linked with libsem.
 */
#ifndef SEM_H
#define SEM_H

typedef int sem_t;

/* semaphore actions */
#define SEM_CREATE      1
#define SEM_TAKE        2
#define SEM_GIVE        3
#define SEM_FLUSH       4
#define SEM_DELETE      5
#define SEM_PROCEXIT    6
#define SEM_VALUE       7       

/* semaphore types */
#define SEM_MUTEX       1
#define SEM_BINARY      2
#define SEM_COUNTING    3

/* semaphore return values */
#define SEM_INVALID_HANDLER     1
#define SEM_INVALID_TYPE        2
#define SEM_INVALID_VALUE       3
#define SEM_INVALID_SIZE        4
#define SEM_INVALID_BLOCK       5
#define SEM_NO_AVAILABLE        6
#define SEM_INVALID_MUTEX_GIVE  7
#define SEM_ALREADY_FREE        8
#define SEM_IN_USE              9

#ifndef OK
#define OK                      0
#endif

/* sem_take block types */
#define WAIT_FOREVER    0
#define NO_WAIT         1

/* message fields for IPC */
#define SEM_F_TYPE      m1_i1
#define SEM_F_VALUE     m1_i2
#define SEM_F_SIZE      m1_i3
#define SEM_F_HANDLER   m1_i1
#define SEM_F_BLOCK     m1_i2
#define SEM_F_ENDPT     m1_i1

#ifndef _SYSTEM
/* library function prototypes */
_PROTOTYPE(int sem_b_create, (sem_t *handler, int value));
_PROTOTYPE(int sem_m_create, (sem_t *handler));
_PROTOTYPE(int sem_c_create, (sem_t *handler, int value, int size));
_PROTOTYPE(int sem_take, (sem_t handler, int block));
_PROTOTYPE(int sem_give, (sem_t handler));
_PROTOTYPE(int sem_flush, (sem_t handler));
_PROTOTYPE(int sem_delete, (sem_t handler));
_PROTOTYPE(int sem_value, (sem_t handler, int *value));
#endif

#endif

