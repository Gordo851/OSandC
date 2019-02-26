#ifndef _sem_c_
#define _sem_c_

#include <semaphore.h>
#include <pthread.h>

#define SEMNAME "/semaphore"


extern sem_t * createSemaphore(char *semname);
extern sem_t * loadSemaphore(char *semname);

extern void unlockSemaphore(char *semname);
extern void lockSemaphore(char *semname);

#endif
