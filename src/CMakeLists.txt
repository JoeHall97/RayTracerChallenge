add_executable(RayTracerChallenge main.cpp)
add_subdirectory(RayTracerChallenge_Lib)
target_link_libraries(RayTracerChallenge PRIVATE rtc::lib)

set_property(TARGET RayTracerChallenge PROPERTY CXX_STANDARD 23)
set_property(TARGET RayTracerChallenge PROPERTY CXX_STANDARD_REQUIRED ON)
