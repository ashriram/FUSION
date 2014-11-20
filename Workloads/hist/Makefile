CC=g++-4.6
CFLAGS=-c -Wall -std=c++0x -g -m32 -pg  -I../../libroi/
LDFLAGS=
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=hist

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -m32 -pg $(OBJECTS) -o $@ $(LDFLAGS) 

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -rf *.o process
