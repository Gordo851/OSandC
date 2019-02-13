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
int createSHM(char * shname)
{
#error FILL IN
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
#error FILL IN
}

/* Access Existing SHM
 *
 * From an existing SHM file descriptor, allocate the SHMstruct and
 * return its pointer.
 *
 * @param fd File descriptor of existing SHM
 * @return Pointer to SHMstruct
 */
SHMstruct * accessSHM(int fd) {
#error FILL IN
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
#error FILL IN
}

/* De-allocate SHMstruct
 *
 * Function de-allocates an already existing SHMstruct.
 *
 * @param shm Pointer to SHMstruct
 */
void clearSHM(SHMstruct * shm)
{
#error FILL IN
}

/* Close SHM file descriptor
 *
 * Function closes an existing SHM file descriptor.
 *
 * @param fd File descriptor of SHM
 */
void closeSHM(int fd)
{
#error FILL IN
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
#error FILL IN
}
