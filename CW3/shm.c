#include <stdbool.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "shm.h"

/* Generate a human-readable timestamp */
char * getTimeStamp() {
    time_t ltime = time(NULL);
    return strtok(ctime(&ltime), "\n");
}

/* Create Shared Memory Segment
 *
 * Function creates a named SHM file descriptor on the filesystem.
 *
 * @param shname Name of SHM
 * @return file descriptor
 */
 # IPC_CREATE means that the program will make a new shm space. Without that key the system hunts for an already existing shm. Like in loadSHM below
 # 0666 sets read/write permissions
int createSHM(char * shname)
{
    int key = 9999;
    int shmId;
    shmId = shmget(key, sizeof(SHMstruct), IPC_CREAT | 0666);
    if (shmId == -1)
    {
        printf("Failed");
        exit();
    }
    return shmId;
}

/* Load Shared Memory
 *
 * Function loads an existing named SHM, or gracefully fails
 * when the SHM does not exist.
 *
 * @param shname Name of SHM region
 * @return file descriptor
 */
int loadSHM(char * shname)
{
    int shmId;
    int key = 9999;
    shmId = shmget(key, sizeof(SHMstruct), 0666);
    if (shmId == -1)
    {
        printf("Failed");
        exit();
    }
    return shmId;
}

/* Access Existing SHM
 *
 * From an existing SHM file descriptor, allocate the SHMstruct and
 * return its pointer.
 *
 * @param fd File descriptor of existing SHM
 * @return Pointer to SHMstruct
 */
SHMstruct * accessSHM(int fd)
{
    shname * ptr = (shname*) shmat(fd, NULL, 0);
    if(ptr == (void*)-1)
    {
        printf("Error");
    }
    return ptr;
}

/* Initialise SHM
 *
 * From an existing SHM file descriptor, initilise the SHMstruct variable.
 *
 * HINT: use accessSHM()
 *
 * @param fd File descriptor of SHM
 * @return Pointer to SHMstruct
 */
SHMstruct * initSHM(int fd, SHMstruct *data) {
    accessSHM(fd);
    *ptr=SHMstruct;
}

/* De-allocate SHMstruct
 *
 * Function de-allocates an already existing SHMstruct.
 *
 * @param shm Pointer to SHMstruct
 */
void clearSHM(SHMstruct * shm)
{

}

/* Close SHM file descriptor
 *
 * Function closes an existing SHM file descriptor.
 *
 * @param fd File descriptor of SHM
 */
void closeSHM(int fd)
{
    shname * ptr = (shname*) shmat(fd, NULL, 0);
    int shmdt(ptr);
}

/* Unlink SHM
 *
 * Function destroys an existing SHM assuming that its
 * allocated memory has been de-allocated.
 *
 * @param shname Name of SHM
 */
void destroySHM(char * shname)
{
    shmctl(shmId, IPC_RMID, NULL);
}
