set(DATASTRUCTURE_HEADERS
	"${PROJECT_SOURCE_DIR}/include/RayTracerChallenge/datastructures/coord_tuple.h"
	"${PROJECT_SOURCE_DIR}/include/RayTracerChallenge/datastructures/colour_tuple.h"
	"${PROJECT_SOURCE_DIR}/include/RayTracerChallenge/datastructures/canvas.h"
)

set(DATASTRUCTURE_SOURCES
	coord_tuple.cpp
	colour_tuple.cpp
	canvas.cpp
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