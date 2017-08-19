CC = gcc
CFLAGS = -Wall
LIBRARIES = -lpdcurses
SOURCES = main.c ui.c engine.c keyboard.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = snake.exe

all: $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBRARIES) -o $(EXECUTABLE)

.o: .c
	$(CC) $< $(CFLAGS) -o $@

clean:
	del *.o $(EXECUTABLE)