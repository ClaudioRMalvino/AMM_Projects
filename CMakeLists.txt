cmake_minimum_required(VERSION 4.0)
project(AMM_Projects)

set(CMAKE_CXX_STANDARD 20)

add_executable(monteCarloPi Monte_Carlo_Exercises/monteCarloPi.cpp)
add_executable(isingModel Monte_Carlo_Exercises/isingModel.cpp)

