#include <stdlib.h>
#include <stdbool.h>
#include "infinityStack.h"

static int mockUp = 42; //statically allocated integer
static int *stackTop = &mockUp; // pointer stackTop, initially points to the address of the above statically allocated integer
static int *newStack; // Declaring uninitialized pointer for later use - This will hold the dynamically allocated memory address for the Stack
int stackSize = DEFAULT_STACK_SIZE; // Stack Size is an integer value that hold the size of the stack - initially set to default stack size
int *val; // Declaring uninitialized pointer for later use - For output/printing


int getStackSize()
{
    return stackSize;
}

void setStackSize( int val)
{
    newStack =(int*)realloc(newStack, (val+1)*sizeof(int)); //Reallocating memory to address - held by pointer newStack
    //Since there is a 1-1 correspondence between the stack size and the position of stackTop relative to newStack...
    //...the below line ensure that stackTop point to the correct position in the new stack if the memory location held by newStack changes.
    stackTop= newStack + getStackSize();
    printf("\n");
    stackSize = val;// Setting stackSize to the parameter passed into the function.
    printf("%d bytes allocated at address %d\n",(val+1)*sizeof(int), newStack);
}

void deleteStack()
{
    printf("**Attempting to delete stack...\n ");
    free(*newStack); // freeing memory allocated to newStack
    stackTop = &mockUp; // resetting stackTop pointer to default state
    stackSize=DEFAULT_STACK_SIZE;// resetting stackSize to default state
    printf("...STACK DELETED**\n");
}

int top()
{
   return *stackTop;// As per the specifications - returns the value held at stackTop
}

int pop( int *val)
{  // If stackTop has the same address as the Stack it implies the stack is empty - Error Message produced and 0 is returned - indicating the pop operation failed
    if( stackTop == newStack)
    {
        printf(" \n **STACK IS EMPTY**  \n \n");
        return(0);
    }

    *val=*stackTop;// set's the value of the val pointer to the value of stackTop- For output/printing
    setStackSize(getStackSize()-1); // Each time this line is executed, it reduces the stackSize by one, freeing unused memory beyond the stack size
    stackTop--; // stackTop is decremented - this is, it points to the value on memory block below it's previous value - in this case a block if 4 bytes
    *(stackTop+1)=0; // Not really needed - Just used to TIDY UP
  return(1);
}

int push( int val)
{
   if(stackTop == &mockUp)
{

    newStack= (int*)calloc(DEFAULT_STACK_SIZE + 1, sizeof(int));
    //newStack = (int*)malloc((DEFAULT_STACK_SIZE + 1)*sizeof(int));
    // Can also use malloc, though values are not initialized to zero
    printf("**%d Bytes allocated at address %d ** \n",(DEFAULT_STACK_SIZE + 1)*sizeof(int),newStack);
    printStack(); // printing the stack and memory address of each element

            if(newStack == NULL) //check to ensure memory was allocated - returns 0 if error occurs
            {
                printf("Unable to allocate memory! /n ");

                return 0;
            }

    stackTop = newStack;//stackTop is assigned the memory address on the newly allocated memory - initially  points to the start of the new stack
    printf("Current address of StackTop is %d \n", stackTop);
    printState();

}

   printf( " \nAttempting to push %d to stack... ", val ); //Condition that ensures only allocated memory can be accessed- REDUNDANT FOR INFINITY STACK
    if( stackTop ==  newStack + getStackSize()+1){
        printf(" \n **Stack Overflow, Memory Full**  \n \n");
            return(0);
    }

    setStackSize(getStackSize()+1); // each time this line is executed, the stack size is set to current size + 1
    stackTop++; // stackTop points to position on block of memory ahead - 4 byte blocks
    *stackTop = val; // the value at value val is writen to memory location stackTop
    printf("Stack Size %d \n", getStackSize());
    printf("Element %d was successfully push to the stack \n", val);
    printStack();

    return 1;
}



// Added function to print the stack as an array and also print the memory address of each element
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


