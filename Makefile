CXXFLAGS := $(CXXFLAGS) -g -Wall -std=c++20 -fcoroutines

TARGETS := char_demo datapoint_demo iterator_demo

all: $(TARGETS)
	@echo "Generated executables are:\n  $(TARGETS)\n"
	@echo "Use the following commands to test the applications:"
	@echo "  ./char_demo"
	@echo "  python3 test_temp.py | ./datapoint_demo"
	@echo "  python3 test_temp.py | ./iterator_demo"

clean:
	rm -f $(TARGETS)
	
iterator_demo: src/iterator_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $?
	
datapoint_demo: src/datapoint_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $?

char_demo: src/char_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $?
