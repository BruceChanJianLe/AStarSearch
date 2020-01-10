cmake_minimum_required(VERSION 2.8.3)
project(aStarSearch)

# Use C++17
SET(CMAKE_CXX_FLAGS "-std=c++17")

add_executable(${PROJECT_NAME} main.cpp astar.cpp astar.h)