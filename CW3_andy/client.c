#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "shm.h"
#include "sem.h"


#include <sys/stat.h> 
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#define SEMNAME "/semaphore"
sem_t *sharedsem;




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

    printf("Atempting to create semaphore...\n");

        if((sharedsem = sem_open(SEMNAME, O_CREAT, 0660 , 1))==SEM_FAILED){
            perror("sem_open"); exit(1);
        }

    printf("Semaphore created %p\n", sharedsem);

    // Remember the condition value!!!
    while(shmData->soldOut == false)
    {


        if(shmData->soldOut == false)
        {

             if (sem_wait (sharedsem) == -1) {
	            perror ("sem_wait: SEMNAME"); exit (1);
            }

            fprintf(stdout, "Ticket %d is available for puchase, please wait while i deliborate... \n",shmData->ticket);
            int random_time = rand() %5;
            sleep(random_time);
            shmData->isTaken = true;
            fprintf(stdout, "Ticket was issued at %s. The ticket number is %d. My address is: %p\n", getTimeStamp(), shmData->ticket, shmData);
            fprintf(fp, "Ticket was issued at %s. The ticket number is %d.\n", getTimeStamp() ,shmData->ticket);

            if (sem_post (sharedsem) == -1) {
	            perror ("sem_post: SEMNAME"); exit (1);
                 }

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
