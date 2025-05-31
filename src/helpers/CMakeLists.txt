add_library(helpers STATIC ./helpers.cpp
	"${PROJECT_SOURCE_DIR}/include/RayTracerChallenge/helpers/helpers.h")

target_include_directories(helpers PUBLIC
	"${PROJECT_SOURCE_DIR}/include/RayTracerChallenge/helpers")

add_library(rc::helpers ALIAS helpers)