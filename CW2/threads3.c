#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int done = 0;

void* theMessageSecondThread(void *ID)
{

    printf("I am the second thread. My thread ID: %d. My pID: %d. The first message\n\n", (int)pthread_self(), (int)getpid());
    while (done == 0);{
        //nothing
    }
    printf("I am the second thread. My ID: %d. My pID: %d. The second message\n\n", (int)pthread_self(), (int)getpid());
    pthread_exit(0);
}



int main()
{
    printf("I am the first thread. My thread ID: %d. My pID: %d. The first message\n\n", (int)pthread_self(), (int)getpid());
    pthread_t thread1;
    pthread_create(&thread1, NULL, theMessageSecondThread, NULL);
    printf("I am the first thread. My ID: %d. My pID: %d. The second message\n\n", (int)pthread_self(), (int)getpid());
    done = 1;
    pthread_join(thread1, NULL);

    return 0;
}
