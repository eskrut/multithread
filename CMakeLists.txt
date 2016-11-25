project(parallelTests)
cmake_minimum_required(VERSION 3.0)

add_subdirectory(pthread)

option(MAKE_WINAPI_TEST "Make winapi test" OFF)
if(MAKE_WINAPI_TEST)
    add_subdirectory(winapi)
endif()

add_subdirectory(std_thread)

add_subdirectory(std_future)

add_subdirectory(threadpool)

add_subdirectory(datarace)

option(MAKE_STL_PARALLEL_TEST "Make stl parallel tests" OFF)
if(MAKE_STL_PARALLEL_TEST)
    add_subdirectory(std_parallel)
endif()

option(MAKE_BOOST_THREAD_TEST "Make stl parallel tests" ON)
if(MAKE_BOOST_THREAD_TEST)
    add_subdirectory(boost_thread)
endif()

option(MAKE_OPENMP_TEST "Make OpenMP tests" OFF)
if(MAKE_OPENMP_TEST)
    add_subdirectory(openmp)
endif()
