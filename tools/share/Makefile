CC=g++-4.6
CFLAGS=-c -Wall  -std=c++0x -g
CFLAGS+=-I/p/amoeba/shared/lib/lib64/pin-2.12-58423-gcc.4.4.7-linux/extras/xed2-ia32/include
CFLAGS+=-I../../macsim/tools/x86_trace_generator
LDFLAGS=-lz
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=process

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) 

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -rf *.o process
