#include <stdio.h>
#include <stdlib.h>
#include "sem.h"
#include "shm.h"

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

    printf("Atempting to create semaphore...\n");

if((sharedsem = sem_open(SEMNAME, O_CREAT, 0660 , 0))==SEM_FAILED){
    perror("sem_open"); exit(1);
}
    printf("Semaphore created %p\n", sharedsem);


    
   


    

    shmData->ticket = ticket;
    shmData->soldOut = false;
    shmData->isTaken = false;
    

    // Remember the condition value!!!
    while(shmData->soldOut == false)
    {
        
        if(shmData->isTaken== true)
        {
            
            if (sem_wait (sharedsem) == -1) {
	                 perror ("sem_wait: SEMNAME"); exit (1);
            }

            shmData->ticket = ticket;
            shmData->isTaken = false;

            if(shmData-> ticket <= MAX_TICKETS){
                shmData->soldOut = false;
            } else{
                shmData->soldOut = true;
            }
            fprintf(stdout, "Ticket was issued at %s. The ticket number is %d. My address is %p\n", getTimeStamp(), ticket-1, shmData);
            fprintf(fp, "Ticket was issued at %s. The ticket number is %d.\n", getTimeStamp() ,ticket-1);

            ticket++;
            if (sem_post (sharedsem) == -1) {
	            perror ("sem_post: SEMNAME"); exit (1);
                 }
        }

        if(ticket == 1){
            ticket++;
        }

        sleep(1);

        // while(shmData->isTaken == false)
        // {
        //     sleep(1);
        // }
        // shmData->isTaken = false;
        // shmData->ticket = ticket;
        // fprintf(stdout, "Ticket was issued at %s. The ticket number is %d. My address is %p\n", getTimeStamp(), ticket, shmData);
        // fprintf(fp, "Ticket was issued at %s. The ticket number is %d.\n", getTimeStamp() ,ticket);
        // if (ticket == 10)
        // {
        //     SHMstruct newdata = {ticket, false, true};
        //     shmData = initSHM(shmFd, &newdata);
        // }
        // ticket ++;
    }


    fprintf(stderr, "Shared Memory Area destroyed\n");
    clearSHM(shmData);
    closeSHM(shmFd);
    destroySHM(SHNAME);
    fclose(fp);

    return EXIT_SUCCESS;
}
