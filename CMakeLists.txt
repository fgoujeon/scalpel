# CppParser - Standard C++ programming language parsing library
# Copyright © 2008  Florian Goujeon
#
# This file is part of CppParser.
#
# CppParser is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, version 3 of the License.
#
# CppParser is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with CppParser.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 2.6)
set(CMAKE_VERBOSE_MAKEFILE off)

#project
project(CppParser)
set(LIBRARY_OUTPUT_PATH lib)
set(EXECUTABLE_OUTPUT_PATH bin)

#library
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

#Boost
include(FindBoost)
find_package(
	Boost 1.35.0
	REQUIRED system filesystem thread wave
)
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

#link
target_link_libraries(
	cppparser
	${Boost_LIBRARIES}
)
target_link_libraries(
	test
	${Boost_LIBRARIES}
)

#export
export(
	TARGETS cppparser
    FILE cppparser.cmake
)
