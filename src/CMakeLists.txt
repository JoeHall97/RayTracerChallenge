add_executable(main main.cpp)
add_subdirectory(RayTracerChallenge_Lib)
target_link_libraries(main PRIVATE rtc::lib)
