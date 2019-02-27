#ifndef _sem_c_
#define _sem_c_

#include <semaphore.h>
#include <pthread.h>

#define SEMNAME "/semaphore"


extern sem_t * createSemaphore(char * semname);
extern sem_t * loadSemaphore(char * semname);

extern int unlockSemaphore(sem_t *semname);
extern int lockSemaphore(sem_t *semname);

#endif
