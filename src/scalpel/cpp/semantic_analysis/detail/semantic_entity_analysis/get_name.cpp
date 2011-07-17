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

#include "get_name.hpp"
#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail { namespace semantic_entity_analysis
{

#define MEMBER_VARIABLE_GET_NAME(ENTITY_TYPE) \
template<> \
const std::string& \
get_name<semantic_entities::ENTITY_TYPE>(const semantic_entities::ENTITY_TYPE& entity) \
{ \
	return entity.name(); \
}

#define FREE_FUNCTION_GET_NAME(ENTITY_TYPE) \
template<> \
const std::string& \
get_name<semantic_entities::ENTITY_TYPE>(const semantic_entities::ENTITY_TYPE& entity) \
{ \
	return semantic_entities::get_name(entity); \
}

MEMBER_VARIABLE_GET_NAME(namespace_alias)
MEMBER_VARIABLE_GET_NAME(namespace_)
MEMBER_VARIABLE_GET_NAME(class_)
MEMBER_VARIABLE_GET_NAME(member_class)
MEMBER_VARIABLE_GET_NAME(union_)
MEMBER_VARIABLE_GET_NAME(member_union)
MEMBER_VARIABLE_GET_NAME(typedef_)
MEMBER_VARIABLE_GET_NAME(member_typedef)
MEMBER_VARIABLE_GET_NAME(simple_member_function)
MEMBER_VARIABLE_GET_NAME(simple_function)
MEMBER_VARIABLE_GET_NAME(variable)
MEMBER_VARIABLE_GET_NAME(member_variable)
MEMBER_VARIABLE_GET_NAME(static_member_variable)
MEMBER_VARIABLE_GET_NAME(bit_field)

FREE_FUNCTION_GET_NAME(declarative_region_t)
FREE_FUNCTION_GET_NAME(open_declarative_region_t)
FREE_FUNCTION_GET_NAME(enum_t)
FREE_FUNCTION_GET_NAME(member_enum_t)

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis

