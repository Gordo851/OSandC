all: server client

ifdef OSX
CC      = gcc
CCFLAGS = -Wall
LIBS    =

else
CC      = gcc
CCFLAGS = -Wall
LIBS    += -pthread -lrt
endif

server: server.c sem.c shm.h sem.h shm.o
	$(CC) $(CCFLAGS) $(LIBS) shm.o -o $@ $<

client: client.c sem.c shm.h sem.h shm.o
	$(CC) $(CCFLAGS) $(LIBS) shm.o -o $@ $<

shm.o: shm.c
	$(CC) $(CCFLAGS) $(LIBS) -c $<

clean:
	$(RM) *.out
