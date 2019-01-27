#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

static int mockUp = 42;
static int *stackTop = &mockUp;
int *newStack=NULL;
int *topOfStack=NULL;

int *currentStack;
int stackSize;

int getStackSize()
{
  if(topOfStack==NULL&&newStack==NULL){
  stackSize=0;
  }
  else{
  stackSize=topOfStack-(newStack+1);
  }
  return stackSize;
}

void setStackSize( int size)
{
    if(size==0){
   newStack=realloc(newStack,1*sizeof(int));
   topOfStack = newStack+1;
   printf("The address of the start of my array %d and the address at the end %d\n",newStack+1,topOfStack);
   stackTop = newStack;
    }
    else{
 newStack=realloc(newStack,(size+1)*sizeof(int));
 if(newStack == NULL)                         //to check if the memory is allocated
    {
        printf("Error! memory not allocated.");
        exit(0);
    }
 topOfStack = (newStack+1) + size;
 printf("The address of the start of my array %d and the address at the end %d\n",(newStack+1),topOfStack);

 if (currentStack>=topOfStack){
    currentStack = topOfStack;
    stackTop = currentStack-1;
 }
}
}

void deleteStack()
{
    free(newStack);
    newStack = NULL;
}

int top()
{
   return *stackTop;
}

int pop( int *val)
{
    if (stackTop == newStack) {

        return 0;
    }
    *val = *stackTop;
    currentStack=currentStack-1;
    stackTop=stackTop-1;
  return 1;
}

int push( int val)
{
    if (newStack==NULL){
    newStack =(int*)malloc((DEFAULT_STACK_SIZE+1)*sizeof(int));
     if(newStack == NULL)                               //to check if the memory is allocated
    {
        printf("Error! memory not allocated.");
        exit(0);
    }
    *newStack = 0;
    currentStack = newStack+1;
    topOfStack = (newStack+1)+DEFAULT_STACK_SIZE;
    printf("The address of the start of my array %d and the address at the end %d\n",(newStack+1),topOfStack);
    }
    if(currentStack>=topOfStack){
    return 0;
    }
    else{
    *currentStack = val;
    currentStack = currentStack + 1;
    stackTop = currentStack-1;

    printf("The value %d saved in the address %d\n",val,stackTop);

    return 1;
    }

}
