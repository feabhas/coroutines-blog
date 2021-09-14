CFLAGS := -g -Wall -std=c++20 -fcoroutines

OBJS := $(SOURCES:.cpp=.o)

all:
	echo "Use 'make simple' or 'make full' to build 'application'"

full: src/full.cpp
	g++ $(CFLAGS) -o full src/full.cpp

simple: src/simple.cpp
	g++ $(CFLAGS) -o simple src/simple.cpp
