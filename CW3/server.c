#include <stdio.h>
#include <stdlib.h>

#include "shm.h"

int main()
{
    FILE * fp;
    int shmFd;
    SHMstruct initData = { 0, false, false};
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
    shmData->ticket = 1;

    fprintf(stdout, "Ticket was issued at %s. The ticket number is %d. My address is %p\n", getTimeStamp(), ticket, shmData);
    fprintf(fp, "Ticket was issued at %s. The ticket number is %d.\n", getTimeStamp() ,ticket);
    shmData->ticket = ticket;
    shmData->soldOut = false;
    shmData->isTaken = false;


    // Remember the condition value!!!
    while(shmData->soldOut == false)
    {
        if(shmData->isTaken== true)
        {
            fprintf(stdout, "Ticket was issued at %s. The ticket number is %d. My address is %p\n", getTimeStamp(), ticket, shmData);
            fprintf(fp, "Ticket was issued at %s. The ticket number is %d.\n", getTimeStamp() ,ticket);
            shmData->ticket = ticket;
            shmData->isTaken = false;

            if(shmData-> ticket < MAX_TICKETS){
                shmData->soldOut = false;
            } else{
                shmData->soldOut = true;
            }
            ticket++;

        }

        if(ticket == 1){
            ticket++;
        }

    }


    fprintf(stderr, "Shared Memory Area destroyed\n");
    clearSHM(shmData);
    closeSHM(shmFd);
    destroySHM(SHNAME);
    fclose(fp);

    return EXIT_SUCCESS;
}
