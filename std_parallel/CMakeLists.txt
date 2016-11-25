cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-std=c++1y")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp" )
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fopenmp")

add_executable(std_parallel std_parallel.cpp)
