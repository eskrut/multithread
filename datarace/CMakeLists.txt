cmake_minimum_required(VERSION 3.0)
project(datarace)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

option(TUNE_THREAD_SANITIZER "Perform thread error sanitizing" OFF)

if(TUNE_THREAD_SANITIZER)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread -fPIC -fPIE" )
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=thread -pie")
endif()

add_executable(datarace datarace.cpp)
