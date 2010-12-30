# Scalpel - Source Code Analysis, Libre and PortablE Library
# Copyright © 2008 - 2010  Florian Goujeon
#
# This file is part of Scalpel.
#
# Scalpel is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Scalpel is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 2.6)

#project
project(Scalpel.Test)
set(EXECUTABLE_OUTPUT_PATH bin)

#executable
file(
	GLOB_RECURSE sources
	src/*.cpp
	src/*.h
)
add_executable(
	test
	${sources}
)

#Scalpel
include_directories(
	../src
)

#cpp2xml
include_directories(
	../cpp2xml/src
)

#Boost
include(FindBoost)
find_package(
	Boost 1.36.0
	REQUIRED program_options
)
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

#link
target_link_libraries(
	test
	scalpel
	cpp2xml
	${Boost_LIBRARIES}
)
