#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include "shm.h"
#include "sem.h"

int main()
{
    FILE * fp;
    int shmFd;
    SHMstruct * shmData;
    sem_t * Semaphore;

    fp = fopen("./tmp/client.log", "a");
    if(fp == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    shmFd = loadSHM(SHNAME);
    shmData = accessSHM(shmFd);
    Semaphore = loadSemaphore(SEMNAME);
    // Remember the condition value!!!
    while(shmData->soldOut == false)
    {
        lockSemaphore(Semaphore);
        while(shmData->isTaken == true)
        {
            sleep(1);
        }

        if(shmData->ticket > 0)
        {
            fprintf(stdout, "Ticket was issued at %s. The ticket number is %d. My address is: %p\n", getTimeStamp(), shmData->ticket, shmData);
            fprintf(fp, "Ticket was issued at %s. The ticket number is %d.\n", getTimeStamp() ,shmData->ticket);
        }
        sleep(1);
        shmData->isTaken = true;
        unlockSemaphore(Semaphore);
    }

    clearSHM(shmData);
    closeSHM(shmFd);
    fclose(fp);

    return EXIT_SUCCESS;
}
