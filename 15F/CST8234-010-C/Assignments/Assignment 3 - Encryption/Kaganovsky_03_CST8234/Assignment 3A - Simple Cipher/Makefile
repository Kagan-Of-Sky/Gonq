CC     = gcc
CFLAGS = -Wall -Wextra -ansi -pedantic


OBJECTS    = cipher.o

EXECUTABLE = cipher


build: $(OBJECTS)
	$(CC) -o $(EXECUTABLE) $(OBJECTS) $(CFLAGS)

cipher.o: cipher.h cipher.c
	$(CC) -c cipher.c $(CFLAGS)

clean:
	rm *.o