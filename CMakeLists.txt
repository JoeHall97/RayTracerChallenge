cmake_minimum_required(VERSION 3.26)
project(RayTracerChallenge CXX)

# needed for clangd to index the project within neovim
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(exercises)

