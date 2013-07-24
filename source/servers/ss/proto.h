/* Function prototypes for semaphore server */

/* ss.c */
_PROTOTYPE(void init, (void) );
_PROTOTYPE(int sem_create, (int type, int value, int size));
_PROTOTYPE(int sem_take, (int sem_handler, int block));
_PROTOTYPE(int sem_give, (int sem_handler));
_PROTOTYPE(int sem_flush, (int sem_handler));
_PROTOTYPE(int sem_delete, (int sem_handler));
_PROTOTYPE(int procexit, (int endpoint));
_PROTOTYPE(int sem_value,(int sem_handler));

