cmake_minimum_required(VERSION 3.5)
project(AstarMaze)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find raylib package if installed globally, otherwise set the path to Raylib manually
find_package(raylib 4.0 QUIET) # Look for Raylib 4.0 or later

# If Raylib wasn't found, download and build it from source
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 4.5.0 # You can set a specific tag here
    )
    FetchContent_MakeAvailable(raylib)
endif()

# Add executable and link Raylib
add_executable(AstarMaze src/main.cpp)
target_link_libraries(AstarMaze raylib)

