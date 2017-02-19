cmake_minimum_required(VERSION 3.6)
project(proj0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES driver.cpp Graph.cpp Graph.h Driver.cpp)
add_executable(proj0 ${SOURCE_FILES})