#define DEFAULT_STACK_SIZE 0 // DEFAULT_STACK_SIZE set to zero for infinity stack

extern void setStackSize( int size);
extern int getStackSize();
extern void deleteStack();
extern int top();
extern int pop(  int* val);
extern int push( int val);

