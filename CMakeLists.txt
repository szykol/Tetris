cmake_minimum_required(VERSION 3.12)

project(Tetris)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
option(BUILD_SANDBOX "Decide whether to build the Sandbox app alongside Skeleton" OFF)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(CUSTOM_RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/res" CACHE INTERNAL "")
add_definitions(-DCUSTOM_RESOURCES_DIR="${CUSTOM_RESOURCES_DIR}")

IF(CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "Building with debug mode")
    add_definitions(-DPROJ_DEBUG)
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

find_package(SFML 2.5 COMPONENTS graphics window audio network system REQUIRED)

add_subdirectory(vendor/Skeleton)
add_subdirectory(src)
