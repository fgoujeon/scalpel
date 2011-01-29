# Scalpel - Source Code Analysis, Libre and PortablE Library
# Copyright © 2008 - 2011  Florian Goujeon
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

#Project
project(Scalpel)
set(LIBRARY_OUTPUT_PATH lib)

#GCC settings
if(CMAKE_COMPILER_IS_GNUCXX)
	add_definitions(-std=c++0x -W -Wall -pedantic)
endif(CMAKE_COMPILER_IS_GNUCXX)

#Check for required C++0x partial support
include(CheckCXXSourceCompiles)
set(CMAKE_REQUIRED_FLAGS "-std=c++0x")
check_cxx_source_compiles(
	"
	//check for variadic template support
	template<class... Ts>
	struct test;

	int main()
	{
		//check for auto-typed variable support
		auto number = 42;

		return 0;
	}
	"
	cxx0x_test
)
if(${cxx0x_test})
else(${cxx0x_test})
	message(
		FATAL_ERROR
		"Your compiler doesn't support the C++Ox features required to build Scalpel.\n"
		"Please use one of the following compilers (non-exhaustive list):\n"
		"\t- g++ 4.4 or later"
	)
endif(${cxx0x_test})

#Library
file(
	GLOB_RECURSE sources
	src/*.cpp
)
add_library(
	scalpel
	SHARED
	${sources}
)
include_directories(src/)

#Boost
include(FindBoost)
find_package(
	Boost 1.36.0
	REQUIRED wave
)
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

#Linking
target_link_libraries(
	scalpel
	${Boost_LIBRARIES}
)

add_subdirectory(
	cpp2xml
)
add_subdirectory(
	test
)
add_subdirectory(
	demo
)

