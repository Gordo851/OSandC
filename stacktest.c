#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

void printState( )
{
  printf( "Size: %d; Top-element: %d.\n", getStackSize(), top());
}

void printPush( int val)
{
  int res;
  res = push(val);
  printf( "\nattempting push( %d)...", val);
  if( res ==0) {
    printf(" failed.\n");
  } else {
    printf(" succeeded.\n");
  }
  printState();
  printStack();
}

void printSetSize( int size)
{
  printf( "executing setStackSize( %d).\n", size);
  setStackSize( size);
  printState();

}

void printPop( )
{
  int val;
  int res;
  res = pop( &val);
  printf( "\n attempting pop( ...) ...");
  if( res ==0) {
    printf(" failed.\n");
  } else {
    printf(" yields %d.\n", val);
  }
  printState();
  printStack();
}

int main()
{


//----------------------------------------------------TEST 1 ADDED BY ANDY - Pushes failing after stack deleted
     printPush(1);
     printPush(2);
     printPush(3);

    deleteStack();
    setStackSize(3);

    int i;
    for(i=4; i <= 16; i++){
         printPush(i);
    }
    deleteStack();
//----------------------------------------------------TEST 1 ADDED BY ANDY

printf("\n \n TEST 2 \n \n");

//----------------------------------------------------TEST 1 ADDED BY ANDY
    deleteStack();
    setStackSize(3);
     printPush(1);
     printPush(2);
     printPush(3);
    printPush(4);

        setStackSize(5);

        printPush(4);
        printPush(5);
        printPush(6);

//    int i;
    for(i=4; i <= 16; i++){
         printPush(i);
    }
//----------------------------------------------------TEST 1 ADDED BY ANDY


/*
  int i;

  printState();
  for( i=1; i<15; i++) {
    printPush(i);
  }

  printSetSize( 9);
  printSetSize( 17);

  for( i=0; i<15; i++) {
    printPop();
  }

  printSetSize( 0);
  printPush(42);
  printPop();

  printSetSize( 1);
  printPush(42);
  printPop();

  return 0;

  */
}


