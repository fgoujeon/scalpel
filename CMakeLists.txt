cmake_minimum_required(VERSION 2.6)
set(CMAKE_VERBOSE_MAKEFILE off)

project(CppParser)
set(EXECUTABLE_OUTPUT_PATH bin)

file(
	GLOB_RECURSE sources
	src/*.cpp
)
file(
	GLOB_RECURSE headers
	src/*.h
)
add_executable(
	Demo
	${sources}
	${headers}
)
