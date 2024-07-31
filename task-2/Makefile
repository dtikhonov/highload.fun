CXXFLAGS=-Wall

all: unique unique-debug

unique: unique.cpp
	g++ $(CXXFLAGS) -O3 -o unique unique.cpp

unique-debug: unique.cpp
	g++ $(CXXFLAGS) -g3 -o unique-debug unique.cpp

clean:
	rm -vf unique unique-debug
