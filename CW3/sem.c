#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#include "sem.h"

sem_t * createSemaphore(char *sem)
{

    printf("creating sem...\n");
    sem_t * semaphore = sem_open (SEMNAME, O_CREAT, O_RDWR,1);
      if(semaphore == SEM_FAILED)
        {
            perror("sem_open");
            printf("Failed");
        }
    if(semaphore != SEM_FAILED)
        {
            printf("semaphore created\n");
        }
    return semaphore;
}


sem_t * loadSemaphore(char * sem)
{
      sem_t *semaphore = sem_open(SEMNAME, O_RDWR);
     if (semaphore == SEM_FAILED) {
        perror("sem_open(3) failed");
        if(semaphore != SEM_FAILED)
        {
            printf("semaphore loaded\n");
        }
    return semaphore;
 }
}

void unlockSemaphore(sem_t * sem)
{
  sem_post(sem);
}

void lockSemaphore(sem_t * sem)
{
   sem_wait(sem);
}


