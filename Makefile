CC=gcc
CFLAGS=-c -Wall -I./core -I./hw
LDFLAGS=
SOURCES=main.c hw/cpu.c hw/memory.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=gbemu


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f \
		$(EXECUTABLE) \
		$(OBJECTS)