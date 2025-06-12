include(FetchContent)
FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(datastructure_tests
	"datastructures/coord_tuple_tests.cpp"
	"datastructures/colour_tuple_tests.cpp"
	"datastructures/canvas_tests.cpp"
	"datastructures/matrix_tests.cpp"
)
target_link_libraries(datastructure_tests PRIVATE
	rtc::helpers 
	rtc::datastructs 
	Catch2::Catch2WithMain
)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(datastructure_tests)
