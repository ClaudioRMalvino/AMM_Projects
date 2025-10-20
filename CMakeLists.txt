cmake_minimum_required(VERSION 4.0)
project(AMM_Projects)

set(CMAKE_CXX_STANDARD 20)

add_executable(AMM_Projects
        Monte_Carlo_Exercises/isingModel.cpp
        Monte_Carlo_Exercises/monteCarloPi.cpp)
