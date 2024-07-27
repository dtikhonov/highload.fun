CXXFLAGS=-Wall

all: simple count count-debug

simple: simple.cpp
	g++ $(CXXFLAGS) -O3 -o simple simple.cpp

count: count.cpp
	g++ $(CXXFLAGS) -O3 -o count count.cpp

count-debug: count.cpp
	g++ $(CXXFLAGS) -g3 -o count-debug count.cpp

clean:
	rm -vf simple count count-debug
