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

#include "final_graph_entities.hpp"

#define GENERATE_GET_ENTITIES_SPECIALIZATION(ENTITY_TYPE, VARIABLE) \
template<> \
std::map<const semantic_entities::ENTITY_TYPE*, semantic_entities::ENTITY_TYPE*>& \
final_graph_entities::get_map_of_type<semantic_entities::ENTITY_TYPE>() \
{ \
	return VARIABLE; \
} \
 \
template<> \
const std::map<const semantic_entities::ENTITY_TYPE*, semantic_entities::ENTITY_TYPE*>& \
final_graph_entities::get_map_of_type<semantic_entities::ENTITY_TYPE>() const \
{ \
	return VARIABLE; \
}

namespace scalpel { namespace cpp { namespace linking { namespace detail
{

GENERATE_GET_ENTITIES_SPECIALIZATION(namespace_, namespaces)
GENERATE_GET_ENTITIES_SPECIALIZATION(class_, classes)
GENERATE_GET_ENTITIES_SPECIALIZATION(member_class, member_classes)
GENERATE_GET_ENTITIES_SPECIALIZATION(enum_, enums)
GENERATE_GET_ENTITIES_SPECIALIZATION(member_enum, member_enums)
GENERATE_GET_ENTITIES_SPECIALIZATION(typedef_, typedefs)
GENERATE_GET_ENTITIES_SPECIALIZATION(member_typedef, member_typedefs)
GENERATE_GET_ENTITIES_SPECIALIZATION(constructor, constructors)
GENERATE_GET_ENTITIES_SPECIALIZATION(destructor, destructors)
GENERATE_GET_ENTITIES_SPECIALIZATION(operator_member_function, operator_member_functions)
GENERATE_GET_ENTITIES_SPECIALIZATION(conversion_function, conversion_functions)
GENERATE_GET_ENTITIES_SPECIALIZATION(simple_member_function, simple_member_functions)
GENERATE_GET_ENTITIES_SPECIALIZATION(operator_function, operator_functions)
GENERATE_GET_ENTITIES_SPECIALIZATION(simple_function, simple_functions)
GENERATE_GET_ENTITIES_SPECIALIZATION(variable, variables)
GENERATE_GET_ENTITIES_SPECIALIZATION(member_variable, member_variables)

}}}} //namespace scalpel::cpp::linking::detail

#undef GENERATE_GET_ENTITIES_SPECIALIZATION

