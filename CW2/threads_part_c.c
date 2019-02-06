#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
static int sig =0;
static int *sig_ptr = &sig;

void* spawned_thread(void *arg)
{
    // Infinite while loop that puts thread to sleep, checks value at static memory location every 0.1 seconds, if it changes from 0, the next block of code is executed
     while(*sig_ptr == 0){
        sleep(0.1);
    }

    // If the value changes, this spawned thread executes this block and terminates. Since the main thread only writes a non-zero entry to the shared static memory once it has..
    // executed it's messages, this block must always be executed after the main thread has printed it's messages first.
    if(*sig_ptr !=0){
        printf("I am the second thread. My thread ID: %d. My pID: %d. The first message\n\n", (int)pthread_self(), (int)getpid());
        printf("I am the second thread. My ID: %d. My pID: %d. The second message\n\n", (int)pthread_self(), (int)getpid());
        pthread_exit(NULL);
    }
}



int main()
{

    pthread_t thread1;
    pthread_create(&thread1, NULL, spawned_thread, NULL);

    //pthread_join(thread1, NULL);

    printf("I am the first thread. My thread ID: %d. My pID: %d. The first message\n\n", (int)pthread_self(), (int)getpid());
    printf("I am the first thread. My ID: %d. My pID: %d. The second message\n\n", (int)pthread_self(), (int)getpid());
    *sig_ptr =1;
    pthread_exit(NULL);


    return 0;
}

