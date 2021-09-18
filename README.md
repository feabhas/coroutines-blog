# coroutines-blog

Demonstration code for the Feabhas coroutines blog.

Build the demos using `make`. Remove generated executables with `make clean`.

Generated executables are:
   * char_demo 
   * datapoint_demo 

Use the following commands to test the applications:

```
$ ./char_demo
$ python3 test_temp.py | ./datapoint_demo
```

Alternatively use `./build.sh` to use `cmake` to build the targets in `build\debug`.

# Using gcc

Coroutine support is available in gcc-10 onwards but requires the 
`-std=c++20` and  `-fcoroutines` command line options. Suitable commands are
of the form:

```
$ g++  -g -Wall -std=c++20 -fcoroutines -o char_demo src/char_demo.cpp
```

## Using clang

Coroutine support is experimental in clang-12 (the latest version at the time
of writing the blog) and needs the include statment:

```
#include <experimental/coroutine>
```

Coroutine support is in the `std::experimental` namespace rather then `std::`.

Make sure `libc++-12-dev` and `libc++abi-12-dev` are 
also installed when compiling with `clang-12`.

To compile add the `-stdlib=libc++` and  `-fcoroutines-ts` options to the 
`clang-12` command line. Suitable commands are of the form:

```
$ clang++-12  -g -Wall -std=c++20 -stdlib=libc++ -fcoroutines-ts -o char_demo src/char_demo.cpp
```
