CXXFLAGS := $(CXXFLAGS) -g -Wall -std=c++20 -fcoroutines

TARGETS := char_demo datapoint_demo

all: $(TARGETS)
	@echo "Generated executables are:\n  $(TARGETS)\n"
	@echo "Use the following commands to test the applications:"
	@echo "  ./char_demo"
	@echo "  python3 test_temp.py | ./datapoint_demo"

clean:
	rm -f $(TARGETS)
	
datapoint_demo: src/datapoint_demo.cpp src/future.h
	$(CXX) $(CXXFLAGS) -o $@ $?

char_demo: src/char_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $?
