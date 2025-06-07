set(DATASTRUCTURE_HEADERS
	"${PROJECT_SOURCE_DIR}/include/RayTracerChallenge/datastructures/coord_tuple.hpp"
	"${PROJECT_SOURCE_DIR}/include/RayTracerChallenge/datastructures/colour_tuple.hpp"
	"${PROJECT_SOURCE_DIR}/include/RayTracerChallenge/datastructures/canvas.hpp"
	"${PROJECT_SOURCE_DIR}/include/RayTracerChallenge/datastructures/matrix.hpp"
)

set(DATASTRUCTURE_SOURCES
	coord_tuple.cpp
	colour_tuple.cpp
	canvas.cpp
	matrix.cpp
)

add_library(datastructs STATIC 
	${DATASTRUCTURE_SOURCES}	
	${DATASTRUCTURE_HEADERS}	
)

target_include_directories(datastructs PUBLIC 
	"${PROJECT_SOURCE_DIR}/include/RayTracerChallenge/datastructures")

target_link_libraries(datastructs
	PRIVATE
		rc::helpers
)