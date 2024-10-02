cmake_minimum_required(VERSION 3.28)
project(Cow3D)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        sdl3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL
        GIT_TAG 1e9ff72
)
set(SDL_SHARED OFF CACHE BOOL "")
set(SDL_STATIC ON CACHE BOOL "")
FetchContent_MakeAvailable(sdl3)
include_directories(${sdl3_SOURCE_DIR}/include)

file(GLOB_RECURSE COW3D_SOURCES
        "Cow3D/*.c"
        "Cow3D/*.h"
        "Cow3D/*.cpp"
        "Cow3D/*.hpp")

add_library(Cow3D STATIC ${COW3D_SOURCES})

target_include_directories(Cow3D PRIVATE /)

target_link_libraries(Cow3D SDL3-static opengl32)


# Find and add the examples
file(GLOB EXAMPLES_SOURCES "example/*.cpp")

foreach(EXAMPLE_SOURCE ${EXAMPLES_SOURCES})
    # Get the filename without extension for the executable name
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)

    add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE})

    # Link the executable with Cow3D and other required libraries
    target_link_libraries(${EXAMPLE_NAME} Cow3D SDL3-static opengl32)

    # Add include directories if needed
    target_include_directories(${EXAMPLE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()
