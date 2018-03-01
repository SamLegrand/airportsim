cmake_minimum_required(VERSION 3.8)
project(airportsim)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp; tinystr.cpp; tinystr.h; tinyxml.cpp; tinyxml.h; tinyxmlerror.cpp; tinyxmlparser.cpp airport.cpp airport.h runway.cpp runway.h airplane.cpp airplane.h)
add_executable(airportsim ${SOURCE_FILES})