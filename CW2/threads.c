#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

void* theMessageSecondThread(void *ID)
{
    void* a;
    printf("I am the second thread. My thread ID: %d. My pID: %d. The first message\n\n", (int)pthread_self(), (int)getpid());
    printf("I am the second thread. My ID: %d. My pID: %d. The second message\n\n", (int)pthread_self(), (int)getpid());
    pthread_exit(a);
}



int main()
{
    void* ret = NULL;
    pthread_t thread1;
    pthread_create(&thread1, NULL, theMessageSecondThread, NULL);
    pthread_join(thread1, ret);
    printf("I am the first thread. My thread ID: %d. My pID: %d. The first message\n\n", (int)pthread_self(), (int)getpid());
    printf("I am the first thread. My ID: %d. My pID: %d. The second message\n\n", (int)pthread_self(), (int)getpid());



    return 0;
}

