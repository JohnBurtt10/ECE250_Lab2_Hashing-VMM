all: Process.cpp OrderedHash.cpp OpenHash.cpp main.cpp
	g++ -g -std=c++11 Process.cpp OrderedHash.cpp OpenHash.cpp main.cpp