CC     = gcc
CFLAGS = -Wall -Wextra -ansi -pedantic


OBJECTS    = transpo.o

EXECUTABLE = transpo


build: $(OBJECTS)
	$(CC) -o $(EXECUTABLE) $(OBJECTS) $(CFLAGS)

cipher.o: transpo.h transpo.c
	$(CC) -c transpo.c $(CFLAGS)

clean:
	rm *.o