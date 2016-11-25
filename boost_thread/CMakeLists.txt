cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-std=c++11")

find_package(Boost COMPONENTS thread REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(treadsBoost boost_thread.cpp)
target_link_libraries(treadsBoost ${Boost_LIBRARIES})
