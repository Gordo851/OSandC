#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

void Problem3()
{
    printf("My process number is: %d\n", (int) getpid());
    int num = 20;
    int num1 = 20;
    int count = 0;
    int count1 = 0;
    char buf;
    int fd1[2];
    if(pipe(fd1)==-1)
    {
        printf("pipe failed.\n");
    }

    pid_t x = fork();

    if (x < 0) //Fork failed
    {
        printf("Fork Failed...\n");
    }
    if (x == 0) //This is the Child.
    {
        close(fd1[1]);
        read(fd1[0], &buf, 1);
        for(count = 1; count < num; count++) {
            printf("First Message: I am the child. My pID is:%d \n", getpid());
            printf("Second Message: I am now complete. My pID is:%d \n", getpid());
        }

        close(fd1[1]);
        exit(0);
    }
    if (x > 0) //This is the parent.
    {
        close(fd1[0]);
        for(count1 = 1; count1 < num1; count1++) {
            printf("First Message: I am the parent. My pID is: %d\n", (int) getpid());
            printf("Second Message: I am the parent. I am now complete. My pID is: %d\n", (int) getpid());
        }
        write(fd1[1], "A", 1);
        wait(NULL);
        exit(0);
    }
}



int main()
{
    printf("problem 3:\n\n");
    Problem3();
    return 0;
}


