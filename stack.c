#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "stack.h"

static int mockUp = 42;
static int *stackTop = &mockUp;

int *newStack = NULL;
int *topOfStack = 0;
int currentSize;
int stackSize;
int *tmp;

void setStackSize( int size)
{
    if (newStack == NULL) {
    newStack = (int*)malloc(size*sizeof(int));
    stackTop = newStack;
    stackSize = size;
    }
    tmp = (int*)realloc(newStack, (size*sizeof(int)));
    if (tmp == NULL)
    {
        printf("Could not change size, size selected too small for members of array");
    }
    newStack = tmp;
    stackSize = size;
}

int top()
{
   return *stackTop;
}

int pop( int *val)
{
    *val = stackTop;
    stackTop = stackTop - 1;
  return 1;
}
int push(int val)
{

    if(newStack == 0) {
        setStackSize(DEFAULT_STACK_SIZE);
        currentSize = -1;
    }
    if (currentSize == stackSize) {
        printf("%p\n", stackTop);
        return 0;
    }
    {
    stackTop = stackTop + 1;
    printf("%p\n", stackTop);
    *stackTop = val;
    currentSize++;
    return 1;
}
}

int getStackSize()
{
    return (stackSize);
}

void deleteStack()
{
    free(newStack);
    newStack = NULL;
    }

