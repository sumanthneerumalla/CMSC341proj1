cmake_minimum_required(VERSION 3.6)
project(proj0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Graph.cpp Graph.h Driver.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_executable(proj0 ${SOURCE_FILES})