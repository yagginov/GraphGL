# Minimum CMake version
cmake_minimum_required(VERSION 3.16)

# Project name and C++ standard
project(GraphGL LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure the project compiles for Win32
if(NOT CMAKE_GENERATOR_PLATFORM)
    set(CMAKE_GENERATOR_PLATFORM Win32)
endif()

add_compile_options(
    /W4
    /w14640
    /w14265
    /w14296
    /w14305
    /w14545
    /w14546
    /w14547
    /w14549
    /w14905
    # /WX
)

include_directories("${CMAKE_SOURCE_DIR}/dependencies/glm")
include_directories("${CMAKE_SOURCE_DIR}/dependencies/stb")
include_directories("${CMAKE_SOURCE_DIR}/dependencies/freetype/include")
include_directories("${CMAKE_SOURCE_DIR}/dependencies/glew-2.1.0/include")
include_directories("${CMAKE_SOURCE_DIR}/dependencies/glfw-3.4/include")

# Define macros for the compiler
add_definitions(-DGLEW_STATIC -DWIN_32)

# Paths to libraries
link_directories("${CMAKE_SOURCE_DIR}/dependencies/freetype/release static/vs2015-2022/win32")
link_directories("${CMAKE_SOURCE_DIR}/dependencies/glew-2.1.0/lib/Release/Win32")
link_directories("${CMAKE_SOURCE_DIR}/dependencies/glfw-3.4/lib-vc2022")

# Add all files to the executable
file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/src/graph_lib/*.cpp")

# Define the executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE freetype.lib)
target_link_libraries(${PROJECT_NAME} PRIVATE glew32s.lib)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw3.lib)

# Standart libraries
target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
target_link_libraries(${PROJECT_NAME} PRIVATE gdi32)
target_link_libraries(${PROJECT_NAME} PRIVATE user32)
target_link_libraries(${PROJECT_NAME} PRIVATE kernel32)
target_link_libraries(${PROJECT_NAME} PRIVATE shell32)
