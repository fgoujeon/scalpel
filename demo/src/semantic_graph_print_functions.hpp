/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SEMANTIC_GRAPH_PRINT_FUNCTIONS_HPP
#define SEMANTIC_GRAPH_PRINT_FUNCTIONS_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <scalpel/cpp/semantic_graph.hpp>
#include "basic_print_functions.hpp"

namespace semantic_graph_print_functions
{

using namespace scalpel::cpp;
using namespace scalpel::cpp::semantic_entities;

void
print(const semantic_graph& g);

void
print
(
	const type& n,
	const unsigned int indent_level
);

void
print
(
	const built_in_type&
);

void
print
(
	const namespace_& n,
	const unsigned int indent_level
);

void
print
(
	const class_& c,
	const unsigned int indent_level,
	const std::string& access = ""
);

void
print
(
	const class_::access& a
);

void
print
(
	const class_::constructor& c,
	const unsigned int indent_level
);

void
print
(
	const function& f,
	const unsigned int indent_level,
	const std::string& access = ""
);

void
print
(
	const function::parameter& p,
	const unsigned int indent_level
);

void
print
(
	const variable& v,
	const unsigned int indent_level,
	const std::string& access = ""
);

template<class EntityT>
void
print
(
	const class_::member<EntityT>& m,
	const unsigned int indent_level
);



template<class EntityT>
void
print
(
	const class_::member<EntityT>& m,
	const unsigned int indent_level
)
{
	std::string access;
	switch(m.access())
	{
		case class_::access::PUBLIC:
			access = "public";
			break;
		case class_::access::PROTECTED:
			access = "protected";
			break;
		case class_::access::PRIVATE:
			access = "private";
			break;
	}
	print(m.entity(), indent_level, access);
}

} //namespace semantic_graph_print_functions

#endif

