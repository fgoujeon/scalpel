# Socoa - Source Code Analysis Library
# Copyright © 2008  Florian Goujeon
#
# This file is part of Socoa.
#
# Socoa is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Socoa is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with Socoa.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 2.6)
set(CMAKE_VERBOSE_MAKEFILE off)

#project
project(Socoa.Test)
set(CMAKE_BUILD_TYPE Debug)
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

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
if(CMAKE_COMPILER_IS_GNUCXX)
	add_definitions(-std=c++0x)
endif(CMAKE_COMPILER_IS_GNUCXX)

#Boost
include(FindBoost)
find_package(
	Boost 1.36.0
	REQUIRED system filesystem thread wave
)
include_directories(${Boost_INCLUDE_DIRS})

#Socoa
include(
	../socoa.cmake
)
include_directories(
	../src
)

#link
target_link_libraries(
	test
	socoa
	cppunit
)

