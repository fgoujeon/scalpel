cmake_minimum_required(VERSION 2.6)

#project
project(CppParser.Test)
set(EXECUTABLE_OUTPUT_PATH bin)

#executable
file(
	GLOB_RECURSE sources
	src/*.cpp
)
file(
	GLOB_RECURSE headers
	src/*.h
)
add_executable(
	test
	${sources}
	${headers}
)

#gcc settings
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	add_definitions(-Wall -pedantic -Wno-long-long)
endif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

#include CppParser
include_directories(
	../src
)

#link with CppUnit
target_link_libraries(
	test
	cppunit
)

