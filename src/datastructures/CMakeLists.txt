add_library(datastructs STATIC 
	tuple.cpp
	"${PROJECT_SOURCE_DIR}/include/RayTracerChallenge/datastructures/tuple.h")

target_include_directories(datastructs PUBLIC 
	"${PROJECT_SOURCE_DIR}/include/RayTracerChallenge/datastructures")

target_link_libraries(datastructs
	PRIVATE
		rc::helpers
)