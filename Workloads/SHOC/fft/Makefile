CC=gcc
CFLAGS=-c -Wall  -pg -O2 -fno-inline -I../../../libroi 
LDFLAGS=
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=$(shell basename $(CURDIR))

ifndef ARCH
	ARCH=-m64
endif

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p bin
	$(CC) $(ARCH) $(LDFLAGS) $(OBJECTS) -o bin/$@

.c.o:
	$(CC) $(CFLAGS) $(ARCH) $< -o $@

clean:
	rm -f *.o
	rm -rf bin 
