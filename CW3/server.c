#include <stdio.h>
#include <stdlib.h>

#include "shm.h"

int main()
{
    FILE * fp;
    int shmFd;
    SHMstruct initData = { 1, false, false};
    SHMstruct * shmData;
    
    fp = fopen("/tmp/server.log", "a");
    if(fp == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    fprintf(stderr, "Shared Memory Area created\n");
    shmFd = createSHM(SHNAME);
    shmData = initSHM( shmFd, &initData );

    // Remember the condition value!!!
    while()
    {
        // Fill in here
    }

    fprintf(stderr, "Shared Memory Area destroyed\n");
    clearSHM(shmData);
    closeSHM(shmFd);
    destroySHM(SHNAME);
    fclose(fp);

    return EXIT_SUCCESS;
}
