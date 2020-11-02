cmake_minimum_required(VERSION 3.5)
project(GradAssignment)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Weffc++ -pedantic -g -pthread")

add_executable(main src/main.cpp src/Track.cpp src/Track.h src/Simulator.cpp src/Simulator.h)
