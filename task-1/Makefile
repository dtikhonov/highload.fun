CXXFLAGS=-Wall

all: parse-ints parse-ints-debug

parse-ints: parse-ints.cpp
	g++ $(CXXFLAGS) -O3 -o parse-ints parse-ints.cpp

parse-ints-debug: parse-ints.cpp
	g++ $(CXXFLAGS) -g3 -o parse-ints-debug parse-ints.cpp

clean:
	rm -vf parse-ints parse-ints-debug
