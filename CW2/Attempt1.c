#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void Problem1()
{
    printf("My process number is: %d\n", (int) getpid());
    pid_t x = fork();
    if (x < 0 ) //Fork failed
    {
        printf("Fork Failed...\n");
    }
    if (x == 0) //This is the Child.
    {
        printf("First Message: I am the child. My pID is: %d\n", (int) getpid());
        printf("Second Message: I am now complete. My pID is: %d\n", (int) getpid());
        exit(0);
    }
    if (x > 0) //This is the parent.
    {

        printf("First Message: I am the parent. My pID is: %d\n", (int) getpid());
        wait(NULL);
        printf("Second Message: I am now complete. My pID is: %d\n", (int) getpid());

        exit(0);
    }
}



int main()
{
    printf("problem 1:\n\n");
    Problem1();
    return 0;
}

