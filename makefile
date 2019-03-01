PROGRAM=test
CXX=g++
CXXFLAGS=-std=c++11

all: $(PROGRAM)

$(PROGRAM): test.o
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) test.o

test.o: test.cpp vector.hpp
	$(CXX) $(CXXFLAGS) -c test.cpp
