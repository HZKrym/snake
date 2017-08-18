CC = gcc
CFLAGS = -Wall
LIBRARIES = -lpdcurses
SOURCES = main.c ui.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = snake.exe

all: $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBRARIES) -o $(EXECUTABLE)

.o: .c
	$(CC) $< $(CFLAGS) -o $@

clean:
	rm -rf *.o