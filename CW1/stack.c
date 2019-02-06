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
  if(topOfStack==NULL&&newStack==NULL){ //because i want my stack size to be 0 at the start of my program
  stackSize=0;
  }
  else{
  stackSize=topOfStack-(newStack+1);
  }
  return stackSize;
}

void setStackSize( int size)
{
    if(size==0){ // when my stack size goes to zero i want to keep the position of my "hidden" 0 for my stackTop to point there
   newStack=realloc(newStack,1*sizeof(int)); //so i re-allocate a 4bytes memory space for my "hidden" 0
   if(newStack == NULL)            //to check if the memory is allocated
    {
        printf("Error! memory not allocated.");
        exit(0);
    }
   topOfStack = newStack+1;
   printf("The address of the start of my array %d and the address at the end %d\n",newStack+1,topOfStack);//i hide the 0 again
   stackTop = newStack; //my stackTop points to the "hidden" 0
    }
    else{
 newStack=realloc(newStack,(size+1)*sizeof(int)); //re-allocate for (size+1) int
 if(newStack == NULL)                         //to check if the memory is allocated
    {
        printf("Error! memory not allocated.");
        exit(0);
    }
 topOfStack = (newStack+1) + size;
 printf("The address of the start of my array %d and the address at the end %d\n",(newStack+1),topOfStack);

 if (currentStack>=topOfStack){ //if i allocate a smaller chunk of memory i want my current pointer
    currentStack = topOfStack;  //to point at the end of the stack so if i push a new value it will fail
    stackTop = currentStack-1;  //and the stackTop pointer in a memory 4 bytes bellow because my last value is an int
 }                              //so it needs 4 bytes to be stored
}
}

void deleteStack()
{
    printf(" \n Attempting to delete stack... \n\n");
    free(newStack);
    newStack = NULL;
    printf("\n ...Stack Deleted \n \n");

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
    *val = *stackTop; //because i want to pop whatever is the top value of my stack
    currentStack=currentStack-1;
    stackTop=stackTop-1;
  return 1;
}

int push( int val)
{
    if (newStack==NULL){
    newStack =(int*)malloc((DEFAULT_STACK_SIZE+1)*sizeof(int)); //allocate memory space for 11 int(to keep a 0 in the first position)
     if(newStack == NULL)                               //check if the memory is allocated
    {
        printf("Error! memory not allocated.");
        exit(0);
    }
    *newStack = 0; //set 1st int to 0 (so i have 10 more positions)
    currentStack = newStack+1; //start counting from 2nd position to keep 0 "hidden"
    topOfStack = (newStack+1)+DEFAULT_STACK_SIZE; //set pointer at the end of my stack (11th position)
    printf("The address of the start of my array %d and the address at the end %d\n",(newStack+1),topOfStack); //keep the position of 0 hidden and so i show a 40 bytes stack
    }
    if(currentStack>=topOfStack){ //the last value added when the pointer point 4 bytes before the end of stack
    return 0;                     //because an int need 4 bytes to be stored and i don't want to go outside my allocated memory
    }
    else{
    *currentStack = val; // put a value to the 1st position (excluding the position of the "hidden" 0) of my stack
    currentStack = currentStack + 1;//pointer goes to the next position
    stackTop = currentStack-1; //my stackTop pointer must always points at my last added value of my stack
                               //but currentStack points to a new empty position so i use currentStack-1*/

    /*printf("The value %d is going to be saved in the address %d\n",val,stackTop);
    int*i;
    printf("These values are in my stack so far ");
    for(i=newStack+1; i<=stackTop; i++){
    printf("%d ",*i);
    }
    printf("\n"); */
    //printStack();
    return 1;
    }



}

//---------------PRINT FUNCTION - ADDED BY ANDY

void printStack(){

int x;
printf("Stack: ");
for(x = 1; x <= getStackSize(); ++x){
    printf( "%d ", *(newStack+x) );
}
    printf("\n");


    printf("Stack Address: ");
for(x = 1; x <= getStackSize(); ++x){
    printf( "%d ", newStack+x);
}
    printf("\n");

}
