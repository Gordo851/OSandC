#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#include "sem.h"

sem_t * createSemaphore(char *sem)
{

    printf("creating sem");
    sem_t * semaphore = sem_open (sem, O_CREAT|O_RDWR, 0777 , 1);
      if(semaphore == SEM_FAILED)
        {
            perror("sem_open");
            printf("Failed");
        }
    if(semaphore != SEM_FAILED)
        {
            printf("semaphore created");       
        }
    return semaphore;
}


sem_t * loadSemaphore(char * sem)
{
    return sem_open(sem, O_EXCL, S_IRUSR | S_IWUSR);
}

void unlockSemaphore(sem_t * sem)
{
    sem_post(sem);
}

void lockSemaphore(sem_t * sem)
{
    sem_wait(sem);
}


