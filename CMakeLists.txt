cmake_minimum_required(VERSION 2.8.3)
project(aStarSearch)

# use c++17
SET(CMAKE_CXX_FLAGS "-std=c++17")

add_executable(${PROJECT_NAME} main.cpp functions.cpp functions.h)
