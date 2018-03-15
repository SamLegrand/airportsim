cmake_minimum_required(VERSION 3.8)
project(airportsim)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

set(SOURCE_FILES main.cpp tinystr.cpp tinystr.h tinyxml.cpp tinyxml.h tinyxmlerror.cpp airport.cpp airport.h runway.cpp runway.h airplane.cpp airplane.h)
add_executable(airportsim ${SOURCE_FILES})
add_definitions(-std=c++98)