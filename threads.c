#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

pthread_mutex_t mutex;
pthread_cond_t conditional;


void* theMessage(void *ID)
{
    printf("I am the first thread. My thread ID: %d. My pID: %d. The first message\n\n", (int)pthread_self(), (int)getpid());

    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&conditional, &mutex);
    printf("I am the first thread. My ID: %d. My pID: %d. The second message\n\n", (int)pthread_self(), (int)getpid());
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}
void* theMessageSecondThread(void *ID)
{
    printf("I am the second thread. My thread ID: %d. My pID: %d. The first message\n\n", (int)pthread_self(), (int)getpid());


    pthread_mutex_lock(&mutex);
    printf("I am the second thread. My ID: %d. My pID: %d. The second message\n\n", (int)pthread_self(), (int)getpid());
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&conditional);
    pthread_exit(NULL);
}



int main()
{
    pthread_t thread0;
    pthread_t thread1;
    printf("Hello\n");
    pthread_create(&thread0, NULL, theMessage, (void *)&thread0);
    pthread_create(&thread1, NULL, theMessageSecondThread, (void *)&thread1);
    pthread_join(thread1, NULL);

    return 0;
}

