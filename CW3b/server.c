#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include "shm.h"
#include "sem.h"
#include <sys/stat.h>

int main()
{
    FILE * fp;
    int shmFd;
    SHMstruct initData = { 0, false, false};
    SHMstruct * shmData;
    int ticket = 1;
    sem_t * Semaphore;

    fp = fopen("./tmp/server.log", "a");
    if(fp == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    fprintf(stderr, "Shared Memory Area created\n");
    shmFd = createSHM(SHNAME);
    shmData = initSHM( shmFd, &initData );
    Semaphore = createSemaphore(SEMNAME);
    // Remember the condition value!!!
    while(shmData->soldOut == false)
    {
        while(shmData->isTaken == false)
        {
            sleep(1);
        }
        shmData->isTaken = false;
        shmData->ticket = ticket;
        fprintf(stdout, "Ticket was issued at %s. The ticket number is %d. My address is %p\n", getTimeStamp(), ticket, shmData);
        fprintf(fp, "Ticket was issued at %s. The ticket number is %d.\n", getTimeStamp() ,ticket);
        if (ticket == 10)
        {
            SHMstruct newdata = {ticket, false, true};
            shmData = initSHM(shmFd, &newdata);
        }
        ticket ++;
    }


    fprintf(stderr, "Shared Memory Area destroyed\n");
    clearSHM(shmData);
    closeSHM(shmFd);
    destroySHM(SHNAME);
    fclose(fp);

    return EXIT_SUCCESS;
}
