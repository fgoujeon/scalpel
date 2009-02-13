# Socoa - Source Code Analysis Library
# Copyright © 2008, 2009  Florian Goujeon
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

#project
project(Socoa.Test)
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

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

#Socoa
include_directories(
	../src
)

#link
target_link_libraries(
	test
	socoa
)
