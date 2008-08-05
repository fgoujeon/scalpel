cmake_minimum_required(VERSION 2.6)
set(CMAKE_VERBOSE_MAKEFILE off)

project(CppParser CXX)
set(LIBRARY_OUTPUT_PATH lib)

file(
	GLOB_RECURSE sources
	src/*.cpp
)
file(
	GLOB_RECURSE headers
	src/*.h
)
add_library(
	cppparser
	SHARED
	${sources}
	${headers}
)
