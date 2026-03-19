include(FetchContent)
FetchContent_Declare(
        Boost
        GIT_REPOSITORY https://github.com/boostorg/boost
        GIT_TAG boost-1.90.0
)
FetchContent_MakeAvailable(Boost)
