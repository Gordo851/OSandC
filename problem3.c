#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

void Problem3()
{
    printf("My process number is: %d\n", (int) getpid());
    int fd1[2];
    pid_t x = fork();
    if (x < 0) //Fork failed
    {
        printf("Fork Failed...\n");
    }
    if (x == 0) //This is the Child.
    {
        int sig = 0;
        int message;
        close(fd1[1]);
        read(fd1[0], message, 1);
        sig = message;
        if (sig != 1) {
            wait(NULL);
        }
        printf("First Message: I am the child. My pID is:%d \n", getpid());
        printf("Second Message: I am now complete. My pID is:%d \n", getpid());
        close(fd1[0]);
        exit(0);
    }
    if (x > 0) //This is the parent.
    {
        printf("First Message: I am the parent. My pID is: %d\n", (int) getpid());
        printf("Second Message: I am the parent. I am now complete. My pID is: %d\n", (int) getpid());
        int sig = 1;
        close(fd1[0]);
        write(fd1[1], sig, 1);
        close(fd1[1]);
        exit(0);
    }
}



int main()
{
    printf("problem 3:\n\n");
    Problem3();
    return 0;
}


