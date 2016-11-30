CC = g++
OBJECT_FILES = lambda.o
CPPFLAGS = -std=c++11

all:default
default:lambdas

lambdas: $(OBJECT_FILES)
	g++ -o $@ lambda.o 


%.o: %.cpp
	$(CC) -c $(CPPFLAGS) $<

clean:
	rm lambdas lambda.o