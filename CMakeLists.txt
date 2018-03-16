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
set(RELEASE_SOURCE_FILES src/main.cpp src/tinystr.cpp src/tinystr.h src/tinyxml.cpp src/tinyxml.h src/tinyxmlerror.cpp src/airport.cpp src/airport.h src/runway.cpp src/runway.h src/airplane.cpp src/airplane.h src/DesignByContract.h src/utils.cpp src/utils.h src/AirportSim.cpp src/AirportSim.h)

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES src/airport.cpp src/airport.h src/runway.cpp src/runway.h src/airplane.cpp src/airplane.h src/tests.cpp)

# Create RELEASE target
add_executable(airportsim ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(airportsim_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(airportsim_debug gtest)
