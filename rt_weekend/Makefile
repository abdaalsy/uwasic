# Define the compiler and flags
CXX = g++
CXXFLAGS = -Wall -g

# Target to compile the program
all: main

main: main.o
	$(CXX) $(CXXFLAGS) -o main main.o

# Target to run the program
run: all
	./main > test.ppm
	nsxiv test.ppm

# Target to clean up
clean:
	rm -f main main.o
