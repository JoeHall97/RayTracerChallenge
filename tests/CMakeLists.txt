include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(datastructure_tests
        "datastructures/vec4_tests.cpp"
        "datastructures/matrix_tests.cpp"
)
target_link_libraries(datastructure_tests PRIVATE
        rtc::lib
        Catch2::Catch2WithMain
)

set_property(TARGET datastructure_tests PROPERTY CXX_STANDARD 23)
set_property(TARGET datastructure_tests PROPERTY CXX_STANDARD_REQUIRED ON)

add_executable(object_tests
        "objects/canvas_tests.cpp"
        "objects/ray_tests.cpp"
        "objects/intersection_tests.cpp"
        "objects/precompute_tests.cpp"
        "objects/camera_tests.cpp"
        "objects/sphere_tests.cpp"
        "objects/material_tests.cpp"
        "objects/colour_tests.cpp"
        "objects/world_tests.cpp"
)
target_link_libraries(object_tests PRIVATE
        rtc::lib
        Catch2::Catch2WithMain
)

set_property(TARGET object_tests PROPERTY CXX_STANDARD 23)
set_property(TARGET object_tests PROPERTY CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(datastructure_tests)
catch_discover_tests(object_tests)
