CXX = g++
CXXFLAGS = -std=c++11 -g3 -Wall -fopenmp
MKDIR = mkdir -p

LIBS = -lm

clean:
	rm -fr *.o a.out core dist build

directorios:
	$(MKDIR) build dist

main.o: directorios main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o build/main.o

all: clean main.o
	$(CXX) $(CXXFLAGS) -o dist/programa build/main.o $(LIBS)

.DEFAULT_GOAL := all
