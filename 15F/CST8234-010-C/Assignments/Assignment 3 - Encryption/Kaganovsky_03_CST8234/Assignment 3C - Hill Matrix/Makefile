CC     = gcc
CFLAGS = -Wall -Wextra -ansi -pedantic


OBJECTS    = hill.o

EXECUTABLE = hill


build: $(OBJECTS)
	$(CC) -o $(EXECUTABLE) $(OBJECTS) $(CFLAGS)

hill.o: hill.h hill.c
	$(CC) -c hill.c $(CFLAGS)

clean:
	rm *.o
