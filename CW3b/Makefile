all: server client

ifdef OSX
CC      = gcc
CCFLAGS = -Wall
LIBS    = 

else
CC      = gcc
CCFLAGS = -Wall
LIBS    = -lrt
endif

server: server.c shm.h shm.o
	$(CC) $(CCFLAGS) $(LIBS) shm.o -o $@ $<

client: client.c shm.h shm.o
	$(CC) $(CCFLAGS) $(LIBS) shm.o -o $@ $<

shm.o: shm.c	
	$(CC) $(CCFLAGS) $(LIBS) -c $<

clean:
	$(RM) *.out
