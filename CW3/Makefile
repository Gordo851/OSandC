all: server client

ifdef OSX
CC      = gcc
CCFLAGS = -Wall
LIBS    =

else
CC      = gcc
CCFLAGS = -Wall
LIBS    += -lrt -pthread
endif

server: server.c shm.h shm.o sem.c sem.h sem.o
	$(CC) $(CCFLAGS) $(LIBS) shm.o sem.o -o $@ $<

client: client.c shm.h shm.o sem.c sem.h sem.o
	$(CC) $(CCFLAGS) $(LIBS) shm.o sem.o -o $@ $<

shm.o: shm.c
	$(CC) $(CCFLAGS) $(LIBS) -c $<

sem.o: sem.c
	$(CC) $(CCFLAGS) $(LIBS) -c $<

clean:
	$(RM) *.out
