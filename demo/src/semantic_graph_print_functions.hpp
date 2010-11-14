/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
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

using namespace scalpel;
using namespace scalpel::cpp;
using namespace scalpel::cpp::semantic_entities;

void
print_type
(
	const semantic_entities::type_shared_ptr_variant& n,
	const unsigned int indent_level
);

void
print
(
	std::shared_ptr<const fundamental_type>
);

void
print_namespace
(
	std::shared_ptr<const namespace_> n,
	const unsigned int indent_level = 0
);

void
print
(
	std::shared_ptr<const class_> c,
	const unsigned int indent_level
);

void
print_base_class
(
	std::shared_ptr<const class_> c,
	const class_::access acc,
	const bool is_virtual,
	const unsigned int indent_level
);

void
print
(
	std::shared_ptr<const class_::constructor> c,
	const unsigned int indent_level
);

void
print
(
	std::shared_ptr<const class_::destructor> d,
	const unsigned int indent_level
);

void
print
(
	std::shared_ptr<const simple_function> f,
	const unsigned int indent_level
);

void
print
(
	std::shared_ptr<const operator_function> f,
	const unsigned int indent_level
);

void
print
(
	std::shared_ptr<const class_::conversion_function> f,
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
	std::shared_ptr<const variable> v,
	const unsigned int indent_level
);

void
print_typedef
(
	std::shared_ptr<const typedef_> entity,
	const unsigned int indent_level
);

std::string
attribute(const class_::access& a);

std::string
attribute(const semantic_entities::operator_ op);

} //namespace semantic_graph_print_functions

#endif

