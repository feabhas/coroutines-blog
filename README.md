# coroutines-blog

Demonstration code for the Feabhas coroutines blog.

To build and run the simple **const char*** application in `src/simple.cpp` use:

```
$ make simple
$ ./simple
```

To build and run the template version (`src/future.h` and `src/full.cpp`
to read a sequence of timestamps and data values from stdin use:

```
$ make full
$ python3 test_temp.py | ./full
```
