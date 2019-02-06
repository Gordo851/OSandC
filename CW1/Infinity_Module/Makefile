all: infinityStackTest

CCFLAGS = -Wall -pedantic

infinityStackTest: infinityStack.o infinityStackTest.c
	gcc $(CCFLAGS) -o infinityStackTest infinityStackTest.c infinityStack.o

%.o: %.c %.h
	gcc $(CCFLAGS) -c $<

clean:
	$(RM) infinityStackTest infinityStack.o
