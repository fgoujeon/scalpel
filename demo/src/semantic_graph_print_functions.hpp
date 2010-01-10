/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#include "basic_print_functions.hpp"
#include <scalpel/cpp/semantic_graph.hpp>
#include <string>
#include <sstream>
#include <iostream>

namespace semantic_graph_print_functions
{

using namespace scalpel::cpp;
using namespace scalpel::cpp::semantic_entities;

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
	const unsigned int indent_level = 0
);

void
print
(
	const class_& c,
	const unsigned int indent_level,
	const std::string& extra_attributes = ""
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
	const class_::destructor& d,
	const unsigned int indent_level
);

void
print
(
	const simple_function& f,
	const unsigned int indent_level,
	const std::string& extra_attributes = ""
);

void
print
(
	const operator_function& f,
	const unsigned int indent_level,
	const std::string& extra_attributes = ""
);

void
print
(
	const class_::conversion_function& f,
	const unsigned int indent_level
);

void
print
(
	const simple_function::parameter& p,
	const unsigned int indent_level
);

void
print
(
	const variable& v,
	const unsigned int indent_level,
	const std::string& extra_attributes = ""
);

std::string
attribute(const class_::access& a);

std::string
attribute(const semantic_entities::operator_ op);

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
	std::ostringstream extra_oss;
	extra_oss << attribute(m.access());
	print(*m.entity(), indent_level, extra_oss.str());
}

template<class EntityT>
void
print
(
	const class_::function_member<EntityT>& f,
	const unsigned int indent_level
)
{
	std::ostringstream extra_oss;

	extra_oss << attribute(f.access());
	if(f.entity()->static_specified())
		extra_oss << " static=\"true\"";
	if(f.const_qualified())
		extra_oss << " const=\"true\"";
	if(f.volatile_qualified())
		extra_oss << " volatile=\"true\"";
	if(f.inline_specified())
		extra_oss << " inline=\"true\"";
	if(f.virtual_specified())
		extra_oss << " virtual=\"true\"";
	if(f.pure_specified())
		extra_oss << " pure=\"true\"";

	print(*f.entity(), indent_level, extra_oss.str());
}

} //namespace semantic_graph_print_functions

#endif

