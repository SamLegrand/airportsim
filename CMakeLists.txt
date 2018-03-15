cmake_minimum_required(VERSION 3.8)
project(airportsim)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(gtest/include)

# Set Library dir
link_directories(gtest/lib)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES main.cpp tinystr.cpp tinystr.h tinyxml.cpp tinyxml.h tinyxmlerror.cpp airport.cpp airport.h runway.cpp runway.h airplane.cpp airplane.h gate.cpp gate.h tests.cpp)

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES tinystr.cpp tinystr.h tinyxml.cpp tinyxml.h tinyxmlerror.cpp airport.cpp airport.h runway.cpp runway.h airplane.cpp airplane.h gate.cpp gate.h tests.cpp)


# Create RELEASE target
add_executable(airportsim ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(airportsim_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(airportsim_debug gtest)

add_definitions(-std=c++98)