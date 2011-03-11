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

#include "entity_groups.hpp"

#define GENERATE_GET_ENTITY_LIST_SPECIALIZATION(ENTITY_TYPE, VARIABLE) \
template<> \
typename entity_groups_of_type<semantic_entities::ENTITY_TYPE>::type& \
get_entity_groups_of_type<semantic_entities::ENTITY_TYPE>(entity_groups& o) \
{ \
	return o.VARIABLE; \
} \
 \
template<> \
const typename entity_groups_of_type<semantic_entities::ENTITY_TYPE>::type& \
get_entity_groups_of_type<semantic_entities::ENTITY_TYPE>(const entity_groups& o) \
{ \
	return o.VARIABLE; \
}

namespace scalpel { namespace cpp { namespace linking { namespace detail
{

GENERATE_GET_ENTITY_LIST_SPECIALIZATION(namespace_, namespaces)
GENERATE_GET_ENTITY_LIST_SPECIALIZATION(class_, classes)
GENERATE_GET_ENTITY_LIST_SPECIALIZATION(member_class, member_classes)
GENERATE_GET_ENTITY_LIST_SPECIALIZATION(enum_, enums)
GENERATE_GET_ENTITY_LIST_SPECIALIZATION(member_enum, member_enums)
GENERATE_GET_ENTITY_LIST_SPECIALIZATION(typedef_, typedefs)
GENERATE_GET_ENTITY_LIST_SPECIALIZATION(member_typedef, member_typedefs)
GENERATE_GET_ENTITY_LIST_SPECIALIZATION(constructor, constructors)
GENERATE_GET_ENTITY_LIST_SPECIALIZATION(destructor, destructors)
GENERATE_GET_ENTITY_LIST_SPECIALIZATION(operator_member_function, operator_member_functions)
GENERATE_GET_ENTITY_LIST_SPECIALIZATION(conversion_function, conversion_functions)
GENERATE_GET_ENTITY_LIST_SPECIALIZATION(simple_member_function, simple_member_functions)
GENERATE_GET_ENTITY_LIST_SPECIALIZATION(operator_function, operator_functions)
GENERATE_GET_ENTITY_LIST_SPECIALIZATION(simple_function, simple_functions)
GENERATE_GET_ENTITY_LIST_SPECIALIZATION(variable, variables)
GENERATE_GET_ENTITY_LIST_SPECIALIZATION(member_variable, member_variables)

}}}} //namespace scalpel::cpp::linking::detail

#undef GENERATE_GET_ENTITY_LIST_SPECIALIZATION

