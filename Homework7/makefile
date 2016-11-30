CC = g++
OBJECT_FILES = Graph.o main.o WeightedGraph.o DirectedGraph.o DirectedWeightedGraph.o
CPPFLAGS = -std=c++11

default : all
all : GraphImplementation

GraphImplementation: $(OBJECT_FILES)
	g++ -o $@ main.o 


%.o: %.cpp
	$(CC) -c $(CPPFLAGS) $<


clean:
	rm GraphImplementation $(OBJECT_FILES)
