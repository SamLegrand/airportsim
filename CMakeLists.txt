cmake_minimum_required(VERSION 3.6.3)
project(airportsim)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(gtest/include)

# Set Library dir
link_directories(gtest/lib)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES src/main.cpp src/tinystr.cpp src/tinyxml.cpp src/tinyxmlerror.cpp src/tinyxmlparser.cpp src/airport.cpp src/airport.h src/airplane.cpp src/airplane.h src/DesignByContract.h src/utils.cpp src/utils.h src/AirportSim.cpp src/AirportSim.h src/importer.cpp src/importer.h src/runway.cpp src/runway.h src/Exporter.cpp src/Exporter.h)

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES src/tinystr.cpp src/tinyxml.cpp src/tinyxmlerror.cpp src/tinyxmlparser.cpp src/airport.cpp src/airplane.cpp src/AirportSim.cpp src/importer.cpp src/tests.cpp src/domaintests.cpp src/inputtests.cpp src/outputtests.cpp src/utils.cpp src/runway.cpp src/runway.h)

# Create RELEASE target
add_executable(airportsim ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(airportsim_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(airportsim_debug gtest)
