cmake_minimum_required(VERSION 3.26)
project(RayTracerChallenge CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(CTest)
add_subdirectory(src)
add_subdirectory(tests)

