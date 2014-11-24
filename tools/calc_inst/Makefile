CC=g++-4.6
CFLAGS=-c -Wall  -std=c++0x -g
CFLAGS+=-I/p/amoeba/shared/lib/lib64/pin-2.10-41150-gcc.3.4.6-ia32_intel64-linux/extras/xed2-ia32/include
CFLAGS+=-I../../macsim/tools/x86_trace_generator
LDFLAGS=-lz
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=calc_inst

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) 

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -rf *.o calc_inst
