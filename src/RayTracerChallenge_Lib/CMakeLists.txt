set(OBJECTS_HEADERS
        "include/RayTracerChallenge/objects/canvas.hpp"
        "include/RayTracerChallenge/objects/ray.hpp"
        "include/RayTracerChallenge/objects/intersection.hpp"
        "include/RayTracerChallenge/objects/sphere.hpp"
        "include/RayTracerChallenge/objects/object.hpp"
)

set(OBJECTS_SOURCES
        "objects/canvas.cpp"
        "objects/ray.cpp"
        "objects/intersection.cpp"
        "objects/sphere.cpp"
)

set(DATASTRUCTURES_HEADERS
        "include/RayTracerChallenge/datastructures/colour_tuple.hpp"
        "include/RayTracerChallenge/datastructures/coord_tuple.hpp"
        "include/RayTracerChallenge/datastructures/matrix.hpp"
)

set(DATASTRUCTURES_SOURCES
        "datastructures/colour_tuple.cpp"
        "datastructures/coord_tuple.cpp"
        "datastructures/matrix.cpp"
)

set(HELPERS_HEADERS
        "include/RayTracerChallenge/helpers/helpers.hpp"
)

set(HELPERS_SOURCES
        "helpers/helpers.cpp"
)

add_library(rtc_lib STATIC)

target_sources(rtc_lib
        PUBLIC
        FILE_SET rtc_lib_headers
        TYPE HEADERS
        BASE_DIRS include
        FILES ${OBJECTS_HEADERS} ${DATASTRUCTURES_HEADERS} ${HELPERS_HEADERS}
        PRIVATE
        ${OBJECTS_SOURCES} ${DATASTRUCTURES_SOURCES} ${HELPERS_SOURCES}
)

set_property(TARGET rtc_lib PROPERTY CXX_STANDARD 23)
set_property(TARGET rtc_lib PROPERTY CXX_STANDARD_REQUIRED ON)

if (MSVC)
    target_compile_options(rtc_lib PRIVATE /Wall)
else ()
    target_compile_options(rtc_lib PRIVATE -Wall -Wextra -Werror)
endif ()

add_library(rtc::lib ALIAS rtc_lib)
