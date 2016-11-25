project(parallelTests)
cmake_minimum_required(VERSION 3.0)

add_subdirectory(pthread)

option(MAKE_WINAPI_TEST "Make winapi test" OFF)
if(${MAKE_WINAPI_TEST})
    add_subdirectory(winapi)
endif()

add_subdirectory(std_thread)

add_subdirectory(std_future)

add_subdirectory(threadpool)

add_subdirectory(datarace)

option(MAKE_STL_PARALLEL_TEST "Make stl parallel tests" OFF)
add_subdirectory(std_parallel)
