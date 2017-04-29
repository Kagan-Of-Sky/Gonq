C=gcc
CFLAGS=-c -Wall
GLFLAGS=-lglut -lGL -lGLU -lm
SOURCES=main.c spiro.c text.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=spiro

all: $(SOURCES) $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(GLFLAGS) $(OBJECTS) -o $@

.c:.o 
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(EXECUTABLE)
