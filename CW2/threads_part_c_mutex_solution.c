#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

    //README:
    //If the  mutex  is  already  locked,  the  calling thread  shall  block until the mutex becomes available- Property of  pthread_mutex_lock() function
    //Since the main thread locks the mutext before the creation of the spawned thread, it(spawn) must wait for the main thread to release the lock (Which it does after printing it's relevant messages).
    //Upon release, the spawned thread will execute and exit. The main thread waits for this to happen before exiting.

void *thread_function(void *args) {

    pthread_mutex_lock(&lock);// wait until mutex is unlocked
    printf("I am the second thread. My thread ID: %d. My pID: %d. The first message\n\n", (int)pthread_self(), (int)getpid());
    printf("I am the second thread. My ID: %d. My pID: %d. The second message\n\n", (int)pthread_self(), (int)getpid());  // print messages
    pthread_mutex_destroy(&lock);
    pthread_exit(NULL); //terminate
}

main()
{

    pthread_mutex_lock(&lock); //Lock mutex before spawn created
	pthread_t spawn_thread;
    pthread_create(&spawn_thread, NULL, thread_function, NULL); // create spawn thread
    printf("I am the first thread. My thread ID: %d. My pID: %d. The first message\n\n", (int)pthread_self(), (int)getpid());
    printf("I am the first thread. My ID: %d. My pID: %d. The second message\n\n", (int)pthread_self(), (int)getpid()); // print messages
    pthread_mutex_unlock(&lock); // unlock mutex
    pthread_join(spawn_thread, NULL); // wait for spawned thread to exit before returning

    return 0;
}
