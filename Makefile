CXXFLAGS = -Wall -g

Driver.out: Graph.o Driver.o
		g++ $(CXXFLAGS) Graph.o Driver.o -o Driver.out

Graph.o: Graph.cpp Graph.h
		g++ $(CXXFLAGS) -c Graph.cpp Graph.h

Driver.o: Driver.cpp
		g++  $(CXXFLAGS) -c Driver.cpp

make clean:
		rm -rf *.o
		rm -rf *~
		rm -rf *.out

make run:
		make;
		./Driver.out