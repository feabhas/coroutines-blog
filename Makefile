CXXFLAGS := $(CXXFLAGS) -g -Wall -std=c++20 -fcoroutines

TARGETS := char_demo datapoint_demo iterator_demo iterator_move_demo

all: $(TARGETS)
	@echo "Generated executables are:\n  $(TARGETS)\n"
	@echo "Use the following commands to test the applications:"
	@echo "  ./char_demo"
	@echo "  python3 test_temp.py | ./datapoint_demo"
	@echo "  python3 test_temp.py | ./iterator_demo"
	@echo "  ./iterator_move_demo"
		
clean:
	rm -f $(TARGETS)

char_demo: src/char_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $?

datapoint_demo: src/datapoint_demo.cpp src/future.h
	$(CXX) $(CXXFLAGS) -o $@ $?

iterator_demo: src/iterator_demo.cpp src/generator.h
	$(CXX) $(CXXFLAGS) -o $@ $?

iterator_move_demo: src/iterator_move_demo.cpp src/generator.h
	$(CXX) $(CXXFLAGS) -o $@ $?
