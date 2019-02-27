#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include "shm.h"
#include "sem.h"

int main()
{
    FILE * fp;
    int shmFd;
    SHMstruct * shmData;
    sem_t * semaphore = sem_open(SEMNAME, O_EXCL, S_IRUSR | S_IWUSR);
    int semValue;

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
            while(shmData->isTaken == false)
            {
                fprintf(stdout, "Ticket %d is available for purchase, please wait while i deliborate... \n",shmData->ticket);
                int random_time = rand() %5;
                sleep(random_time);
                fprintf(stdout, "Bought at %s. number is %d. My address: %p\n", getTimeStamp(), shmData->ticket, shmData);
                fprintf(fp, "Ticket was issued at %s. The ticket number is %d.\n", getTimeStamp() ,shmData->ticket);
                shmData->isTaken = true;
            }

    }

    clearSHM(shmData);
    closeSHM(shmFd);
    fclose(fp);

    return EXIT_SUCCESS;
}
