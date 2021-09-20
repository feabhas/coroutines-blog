cmake_minimum_required(VERSION 3.16)
project(coroutines LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(
    -fcoroutines
    -Wall
    -Wextra
    -Wconversion
    -Wsign-conversion
    $<$<CONFIG:DEBUG>:-g3>
    $<$<CONFIG:DEBUG>:-Og>
    $<$<CONFIG:RELEASE>:-O3>
)

add_compile_definitions(
    $<$<CONFIG:DEBUG>:DEBUG>
)

add_executable(char_demo src/char_demo.cpp)
add_executable(datapoint_demo src/datapoint_demo.cpp)
add_executable(iterator_demo src/iterator_demo.cpp)
add_executable(iterator_move_demo src/iterator_move_demo.cpp)
