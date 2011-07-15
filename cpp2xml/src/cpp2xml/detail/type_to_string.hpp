/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

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

#ifndef CPP2XML_DETAIL_TYPE_TO_STRING_HPP
#define CPP2XML_DETAIL_TYPE_TO_STRING_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <string>

namespace cpp2xml { namespace detail
{

template<class Entity>
std::string
type_to_string();

#define TYPE_TO_STRING(TYPE, STRING) \
template<> \
inline \
std::string \
type_to_string<scalpel::cpp::semantic_entities::TYPE>() \
{ \
	return STRING; \
}

TYPE_TO_STRING(namespace_, "namespace")
TYPE_TO_STRING(linked_namespace, "linked_namespace")
TYPE_TO_STRING(unnamed_namespace, "unnamed_namespace")
TYPE_TO_STRING(linked_unnamed_namespace, "linked_unnamed_namespace")
TYPE_TO_STRING(class_, "class")
TYPE_TO_STRING(member_class, "member_class")
TYPE_TO_STRING(enum_, "enum")
TYPE_TO_STRING(member_enum, "member_enum")
TYPE_TO_STRING(typedef_, "typedef")
TYPE_TO_STRING(member_typedef, "member_typedef")
TYPE_TO_STRING(constructor, "constructor")
TYPE_TO_STRING(destructor, "destructor")
TYPE_TO_STRING(operator_member_function, "operator_member_function")
TYPE_TO_STRING(conversion_function, "conversion_function")
TYPE_TO_STRING(simple_member_function, "simple_member_function")
TYPE_TO_STRING(operator_function, "operator_function")
TYPE_TO_STRING(simple_function, "simple_function")
TYPE_TO_STRING(variable, "variable")
TYPE_TO_STRING(member_variable, "member_variable")
TYPE_TO_STRING(static_member_variable, "static_member_variable")
TYPE_TO_STRING(bit_field, "bit_field")

#undef TYPE_TO_STRING

}} //namespace cpp2xml::detail

#endif

