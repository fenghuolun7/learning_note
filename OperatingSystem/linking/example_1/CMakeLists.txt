# this experiment is set for demonstrating the difference between
# shared libraries and static libraries.
cmake_minimum_required(VERSION 3.5)

# Set the project name
PROJECT(test_linking C CXX)

add_executable(exmaple_1 main.cpp)
add_executable(exmaple_2 main.cpp)

add_library(static_lib STATIC use_undefined.cpp undefined.cpp)
target_link_directories(static_lib PRIVATE undefined.h)
set_target_properties(static_lib PROPERTIES LINKER_LANGUAGE CXX)

add_library(shared_lib SHARED use_undefined undefined.cpp)
target_link_directories(shared_lib PRIVATE undefined.h)
set_target_properties(shared_lib PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(exmaple_1 static_lib)
target_link_libraries(exmaple_2 shared_lib)