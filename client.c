#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include "shm.h"

int main()
{
    FILE * fp;
    int shmFd;
    SHMstruct * shmData;

    fp = fopen("/tmp/client.log", "a");
    if(fp == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    shmFd = loadSHM(SHNAME);
    shmData = accessSHM(shmFd);

    // Remember the condition value!!!
    while(shmData->isTaken == false && shmData->soldOut == false)
    {
        int thisTicket = shmData->ticket;
        fprintf(stdout, "Ticket was issued at %s. The ticket number is %d.\n", getTimeStamp() ,thisTicket);
        int max = rand();
        int actual = max/1000;
        sleep(actual);
        shmData->isTaken = true;
    }

    clearSHM(shmData);
    closeSHM(shmFd);
    fclose(fp);

    return EXIT_SUCCESS;
}
