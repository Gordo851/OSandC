#include <stdio.h>
#include <stdlib.h>

#include "shm.h"

int main()
{
    FILE * fp;
    int shmFd;
    SHMstruct initData = { 1, false, false};
    SHMstruct * shmData;
    int ticket = 1;

    fp = fopen("./tmp/server.log", "a");
    if(fp == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    fprintf(stderr, "Shared Memory Area created\n");
    shmFd = createSHM(SHNAME);
    shmData = initSHM( shmFd, &initData );

    // Remember the condition value!!!
    while(shmData->soldOut == false)
    {
        if
        SHMstruct newdata = {ticket, false, false};
        shmData = initSHM(shmFd, &newdata);
        fprintf(stdout, "Ticket was issued at %s. The ticket number is %d.\n", getTimeStamp() ,ticket);
        if (ticket == 11)
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
