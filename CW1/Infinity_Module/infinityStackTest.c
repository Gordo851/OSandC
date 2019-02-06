#include <stdlib.h>
#include <stdio.h>
#include "infinityStack.h"

void printState( )
{
  printf( "Size: %d; Top-element: %d.\n", getStackSize(), top());

}

void printPush( int val)
{
  int res;
  res = push(val);
  printf( "attempting push( %d)...", val);
  if( res ==0) {
    printf(" failed.\n");
  } else {
    printf(" succeeded.\n");
  }
  printState();
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
  printf( "attempting pop( ...) ..." );
  if( res ==0) {
    printf(" failed.\n");
  } else {
    printf(" yields %d.\n", val);
  }
  printState();
}

int main()
{

    printf("Testing initial state... \n");
    printState();
    printf("\n");

  int i;
  for( i=1; i<=10; i++) {
    printPush(i);
  }




  for( i=1; i<=11; i++) {
    printPop();
    printStack();
  }


  /* These test are not really relevant to Infinity Stack


  printSetSize( 0);
  printPush(42);
  printPop();

  printSetSize( 1);
  printPush(42);
  printPop();

  */

  return 0;
}



