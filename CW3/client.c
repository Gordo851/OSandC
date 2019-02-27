#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include "sem.h"
#include "shm.h"

int main()
{
    FILE * fp;
    int shmFd;
    SHMstruct * shmData;
    sem_t *sem;

    fp = fopen("./tmp/client.log", "a");
    if(fp == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    shmFd = loadSHM(SHNAME);
    shmData = accessSHM(shmFd);
    sem = createSemaphore(SEMNAME);
    // Remember the condition value!!!
    while(shmData->soldOut == false)
    {
           sem_wait(sem);
            while(shmData->isTaken == false)
            {
                fprintf(stdout, "Ticket %d is available for purchase, please wait while i deliborate... \n",shmData->ticket);
                int random_time = rand() %5;
                sleep(random_time);
                fprintf(stdout, "Bought at %s. number is %d. My address: %p\n", getTimeStamp(), shmData->ticket, shmData);
                fprintf(fp, "Ticket was issued at %s. The ticket number is %d.\n", getTimeStamp() ,shmData->ticket);
                shmData->isTaken = true;
            }
          sem_post(sem);

    }

    clearSHM(shmData);
    closeSHM(shmFd);
    fclose(fp);

    return EXIT_SUCCESS;
}
