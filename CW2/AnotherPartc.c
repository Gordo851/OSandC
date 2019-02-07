#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

pthread_mutex_t Lock1;
pthread_mutex_t Lock2;
pthread_cond_t Condition1;
pthread_cond_t Condition2;

void* theMessageSecondThread(void *ID)
{
    pthread_mutex_lock(&Lock1);
    pthread_cond_wait(&Condition1, &Lock1);
    printf("I am the second thread. My thread ID: %d. My pID: %d. The first message\n\n", (int)pthread_self(), (int)getpid());
    printf("I am the second thread. My ID: %d. My pID: %d. The second message\n\n", (int)pthread_self(), (int)getpid());
    pthread_mutex_unlock(&Lock1);
}

int main()
{
    pthread_t thread0;
    pthread_create(&thread0, NULL, theMessageSecondThread, NULL);
    printf("I am the first thread. My thread ID: %d. My pID: %d. The first message\n\n", (int)pthread_self(), (int)getpid());
    printf("I am the first thread. My ID: %d. My pID: %d. The second message\n\n", (int)pthread_self(), (int)getpid());
    pthread_cond_signal(&Condition1);
    pthread_join(thread0, NULL);
    return 0;
}


