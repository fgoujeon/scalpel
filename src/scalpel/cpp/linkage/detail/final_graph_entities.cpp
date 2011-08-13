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

#define GET_MAP_OF_LINKED_TYPE(ENTITY_TYPE, VARIABLE) \
template<> \
std::map<const typename nonlinked_type<semantic_entities::ENTITY_TYPE>::type*, semantic_entities::ENTITY_TYPE*>& \
final_graph_entities::get_map_of_linked_type<semantic_entities::ENTITY_TYPE>() \
{ \
	return VARIABLE; \
} \
 \
template<> \
const std::map<const typename nonlinked_type<semantic_entities::ENTITY_TYPE>::type*, semantic_entities::ENTITY_TYPE*>& \
final_graph_entities::get_map_of_linked_type<semantic_entities::ENTITY_TYPE>() const \
{ \
	return VARIABLE; \
}

namespace scalpel { namespace cpp { namespace linkage { namespace detail
{

GET_MAP_OF_LINKED_TYPE(linked_namespace, namespaces)
GET_MAP_OF_LINKED_TYPE(linked_unnamed_namespace, unnamed_namespaces)
GET_MAP_OF_LINKED_TYPE(class_, classes)
GET_MAP_OF_LINKED_TYPE(member_class, member_classes)
GET_MAP_OF_LINKED_TYPE(union_, unions)
GET_MAP_OF_LINKED_TYPE(member_union, member_unions)
GET_MAP_OF_LINKED_TYPE(anonymous_union, anonymous_unions)
GET_MAP_OF_LINKED_TYPE(anonymous_member_union, anonymous_member_unions)
GET_MAP_OF_LINKED_TYPE(enum_, enums)
GET_MAP_OF_LINKED_TYPE(member_enum, member_enums)
GET_MAP_OF_LINKED_TYPE(typedef_, typedefs)
GET_MAP_OF_LINKED_TYPE(member_typedef, member_typedefs)
GET_MAP_OF_LINKED_TYPE(constructor, constructors)
GET_MAP_OF_LINKED_TYPE(destructor, destructors)
GET_MAP_OF_LINKED_TYPE(operator_member_function, operator_member_functions)
GET_MAP_OF_LINKED_TYPE(conversion_function, conversion_functions)
GET_MAP_OF_LINKED_TYPE(simple_member_function, simple_member_functions)
GET_MAP_OF_LINKED_TYPE(operator_function, operator_functions)
GET_MAP_OF_LINKED_TYPE(simple_function, simple_functions)
GET_MAP_OF_LINKED_TYPE(variable, variables)
GET_MAP_OF_LINKED_TYPE(member_variable, member_variables)
GET_MAP_OF_LINKED_TYPE(static_member_variable, static_member_variables)
GET_MAP_OF_LINKED_TYPE(bit_field, bit_fields)
GET_MAP_OF_LINKED_TYPE(enum_constant<int>, int_enum_constants)
GET_MAP_OF_LINKED_TYPE(enum_constant<unsigned int>, unsigned_int_enum_constants)
GET_MAP_OF_LINKED_TYPE(enum_constant<long int>, long_int_enum_constants)
GET_MAP_OF_LINKED_TYPE(enum_constant<unsigned long int>, unsigned_long_int_enum_constants)

}}}} //namespace scalpel::cpp::linkage::detail

#undef GET_MAP_OF_LINKED_TYPE

