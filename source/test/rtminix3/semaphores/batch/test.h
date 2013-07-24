#include <stdio.h>
#include <lib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <minix/sem.h>

#define OK              0
#define FAILED          2
#define FATAL_FAILURE   3

#define DEBUGMSG(testnr, str) printf("Test %d %s:%u : %s\n", testnr, __FILE__, __LINE__, str)
