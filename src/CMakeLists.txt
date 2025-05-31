add_executable(main main.cpp)
add_subdirectory(helpers)
add_subdirectory(datastructures)
target_link_libraries(main PRIVATE datastructs)
