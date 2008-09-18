# Socoa - Standard Source Code Analysis Library
# Copyright © 2008  Florian Goujeon
#
# This file is part of Socoa.
#
# Socoa is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, version 3 of the License.
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
project(Socoa)
set(CMAKE_BUILD_TYPE Debug)
set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

#gcc settings
if(CMAKE_COMPILER_IS_GNUCXX)
	add_definitions(-std=c++0x -W -Wall)
endif(CMAKE_COMPILER_IS_GNUCXX)

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
	socoa
	SHARED
	${sources}
	${headers}
)

#Boost
include(FindBoost)
find_package(
	Boost 1.36.0
	REQUIRED system filesystem thread wave
)
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

#link
target_link_libraries(
	socoa
	${Boost_LIBRARIES}
)

#export
export(
	TARGETS socoa
    FILE socoa.cmake
)
