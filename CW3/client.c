#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include "shm.h"

int main()
{
    FILE * fp;
    int shmFd;
    SHMstruct * shmData;

    fp = fopen("./tmp/client.log", "a");
    if(fp == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    shmFd = loadSHM(SHNAME);
    shmData = accessSHM(shmFd);

    // Remember the condition value!!!
    while(shmData->soldOut == false)
    {
        if(shmData->soldOut == false)
        {
            fprintf(stdout, "Ticket %d is available for puchase, please wait while i deliborate... \n",shmData->ticket);
            int random_time = rand() %5;
            sleep(random_time);
            shmData->isTaken = true;
            fprintf(stdout, "Ticket was issued at %s. The ticket number is %d. My address is: %p\n", getTimeStamp(), shmData->ticket, shmData);
            fprintf(fp, "Ticket was issued at %s. The ticket number is %d.\n", getTimeStamp() ,shmData->ticket);

        }

        sleep(1);


        // while(shmData->isTaken == true)
        // {
        //     sleep(1);
        // }
        // if(shmData->ticket > 0)
        // {
        //     fprintf(stdout, "Ticket was issued at %s. The ticket number is %d. My address is: %p\n", getTimeStamp(), shmData->ticket, shmData);
        //     fprintf(fp, "Ticket was issued at %s. The ticket number is %d.\n", getTimeStamp() ,shmData->ticket);
        // }
        // sleep(1);
        // shmData->isTaken = true;
    }

    clearSHM(shmData);
    closeSHM(shmFd);
    fclose(fp);

    return EXIT_SUCCESS;
}
