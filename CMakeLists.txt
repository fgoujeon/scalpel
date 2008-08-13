cmake_minimum_required(VERSION 2.6)
set(CMAKE_VERBOSE_MAKEFILE off)

project(CppParser CXX)
set(LIBRARY_OUTPUT_PATH lib)
set(EXECUTABLE_OUTPUT_PATH bin)

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

add_executable(
	test
	${sources}
	${headers}
)
include(FindBoost)
find_package(
	Boost 1.35.0
	REQUIRED system filesystem thread wave
)
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(
	test
	${Boost_LIBRARIES}
)
