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

#include "get_members.hpp"
#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace generic_queries { namespace detail
{

#define GENERATE_GET_MEMBERS_SPECIALIZATION(PARENT_TYPE, MEMBER_TYPE, PARENT_MEMBER_FUNCTION) \
template<> \
get_members_return_type<PARENT_TYPE, semantic_entities::MEMBER_TYPE, false>::type \
get_members<semantic_entities::MEMBER_TYPE>(semantic_entities::PARENT_TYPE& parent) \
{ \
	return parent.PARENT_MEMBER_FUNCTION(); \
} \
 \
template<> \
get_members_return_type<PARENT_TYPE, semantic_entities::MEMBER_TYPE, true>::type \
get_members<semantic_entities::MEMBER_TYPE>(const semantic_entities::PARENT_TYPE& parent) \
{ \
	return parent.PARENT_MEMBER_FUNCTION(); \
}

#define GENERATE_GET_UNNAMED_NAMESPACE_SPECIALIZATION(PARENT_TYPE, MEMBER_TYPE) \
template<> \
get_members_return_type<PARENT_TYPE, semantic_entities::MEMBER_TYPE, false>::type \
get_members<semantic_entities::MEMBER_TYPE>(semantic_entities::PARENT_TYPE& parent) \
{ \
	semantic_entities::MEMBER_TYPE* entity = parent.get_unnamed_namespace(); \
	if(entity) \
		return utility::single_object_range<semantic_entities::MEMBER_TYPE>(*entity); \
	else \
		return utility::single_object_range<semantic_entities::MEMBER_TYPE>(); \
} \
 \
template<> \
get_members_return_type<PARENT_TYPE, semantic_entities::MEMBER_TYPE, true>::type \
get_members<semantic_entities::MEMBER_TYPE>(const semantic_entities::PARENT_TYPE& parent) \
{ \
	const semantic_entities::MEMBER_TYPE* entity = parent.get_unnamed_namespace(); \
	if(entity) \
		return utility::single_object_const_range<semantic_entities::MEMBER_TYPE>(*entity); \
	else \
		return utility::single_object_const_range<semantic_entities::MEMBER_TYPE>(); \
}

GENERATE_GET_MEMBERS_SPECIALIZATION(namespace_, namespace_, namespaces)
GENERATE_GET_UNNAMED_NAMESPACE_SPECIALIZATION(namespace_, unnamed_namespace)
GENERATE_GET_MEMBERS_SPECIALIZATION(namespace_, class_, classes)
GENERATE_GET_MEMBERS_SPECIALIZATION(namespace_, union_, unions)
GENERATE_GET_MEMBERS_SPECIALIZATION(namespace_, anonymous_union, anonymous_unions)
GENERATE_GET_MEMBERS_SPECIALIZATION(namespace_, enum_, enums)
GENERATE_GET_MEMBERS_SPECIALIZATION(namespace_, typedef_, typedefs)
GENERATE_GET_MEMBERS_SPECIALIZATION(namespace_, operator_function, operator_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION(namespace_, simple_function, simple_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION(namespace_, variable, variables)
GENERATE_GET_MEMBERS_SPECIALIZATION(namespace_, namespace_alias, namespace_aliases)

GENERATE_GET_MEMBERS_SPECIALIZATION(linked_namespace, linked_namespace, namespaces)
GENERATE_GET_MEMBERS_SPECIALIZATION(linked_namespace, linked_unnamed_namespace, unnamed_namespaces)
GENERATE_GET_MEMBERS_SPECIALIZATION(linked_namespace, class_, classes)
GENERATE_GET_MEMBERS_SPECIALIZATION(linked_namespace, union_, unions)
GENERATE_GET_MEMBERS_SPECIALIZATION(linked_namespace, anonymous_union, anonymous_unions)
GENERATE_GET_MEMBERS_SPECIALIZATION(linked_namespace, enum_, enums)
GENERATE_GET_MEMBERS_SPECIALIZATION(linked_namespace, typedef_, typedefs)
GENERATE_GET_MEMBERS_SPECIALIZATION(linked_namespace, operator_function, operator_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION(linked_namespace, simple_function, simple_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION(linked_namespace, variable, variables)

GENERATE_GET_MEMBERS_SPECIALIZATION(unnamed_namespace, namespace_, namespaces)
GENERATE_GET_UNNAMED_NAMESPACE_SPECIALIZATION(unnamed_namespace, unnamed_namespace)
GENERATE_GET_MEMBERS_SPECIALIZATION(unnamed_namespace, class_, classes)
GENERATE_GET_MEMBERS_SPECIALIZATION(unnamed_namespace, union_, unions)
GENERATE_GET_MEMBERS_SPECIALIZATION(unnamed_namespace, enum_, enums)
GENERATE_GET_MEMBERS_SPECIALIZATION(unnamed_namespace, typedef_, typedefs)
GENERATE_GET_MEMBERS_SPECIALIZATION(unnamed_namespace, operator_function, operator_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION(unnamed_namespace, simple_function, simple_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION(unnamed_namespace, variable, variables)
GENERATE_GET_MEMBERS_SPECIALIZATION(unnamed_namespace, namespace_alias, namespace_aliases)

GENERATE_GET_MEMBERS_SPECIALIZATION(linked_unnamed_namespace, linked_namespace, namespaces)
GENERATE_GET_UNNAMED_NAMESPACE_SPECIALIZATION(linked_unnamed_namespace, linked_unnamed_namespace)
GENERATE_GET_MEMBERS_SPECIALIZATION(linked_unnamed_namespace, class_, classes)
GENERATE_GET_MEMBERS_SPECIALIZATION(linked_unnamed_namespace, union_, unions)
GENERATE_GET_MEMBERS_SPECIALIZATION(linked_unnamed_namespace, enum_, enums)
GENERATE_GET_MEMBERS_SPECIALIZATION(linked_unnamed_namespace, typedef_, typedefs)
GENERATE_GET_MEMBERS_SPECIALIZATION(linked_unnamed_namespace, operator_function, operator_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION(linked_unnamed_namespace, simple_function, simple_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION(linked_unnamed_namespace, variable, variables)

GENERATE_GET_MEMBERS_SPECIALIZATION(class_, member_class, classes)
GENERATE_GET_MEMBERS_SPECIALIZATION(class_, member_union, unions)
GENERATE_GET_MEMBERS_SPECIALIZATION(class_, member_enum, enums)
GENERATE_GET_MEMBERS_SPECIALIZATION(class_, member_typedef, typedefs)
GENERATE_GET_MEMBERS_SPECIALIZATION(class_, constructor, constructors)
GENERATE_GET_MEMBERS_SPECIALIZATION(class_, destructor, get_destructor)
GENERATE_GET_MEMBERS_SPECIALIZATION(class_, operator_member_function, operator_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION(class_, conversion_function, conversion_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION(class_, simple_member_function, simple_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION(class_, member_variable, variables)
GENERATE_GET_MEMBERS_SPECIALIZATION(class_, bit_field, bit_fields)

GENERATE_GET_MEMBERS_SPECIALIZATION(member_class, member_class, classes)
GENERATE_GET_MEMBERS_SPECIALIZATION(member_class, member_union, unions)
GENERATE_GET_MEMBERS_SPECIALIZATION(member_class, member_enum, enums)
GENERATE_GET_MEMBERS_SPECIALIZATION(member_class, member_typedef, typedefs)
GENERATE_GET_MEMBERS_SPECIALIZATION(member_class, constructor, constructors)
GENERATE_GET_MEMBERS_SPECIALIZATION(member_class, destructor, get_destructor)
GENERATE_GET_MEMBERS_SPECIALIZATION(member_class, operator_member_function, operator_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION(member_class, conversion_function, conversion_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION(member_class, simple_member_function, simple_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION(member_class, member_variable, variables)
GENERATE_GET_MEMBERS_SPECIALIZATION(member_class, bit_field, bit_fields)

GENERATE_GET_MEMBERS_SPECIALIZATION(union_, member_class, classes)
GENERATE_GET_MEMBERS_SPECIALIZATION(union_, member_union, unions)
GENERATE_GET_MEMBERS_SPECIALIZATION(union_, member_enum, enums)
GENERATE_GET_MEMBERS_SPECIALIZATION(union_, member_typedef, typedefs)
GENERATE_GET_MEMBERS_SPECIALIZATION(union_, constructor, constructors)
GENERATE_GET_MEMBERS_SPECIALIZATION(union_, destructor, get_destructor)
GENERATE_GET_MEMBERS_SPECIALIZATION(union_, operator_member_function, operator_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION(union_, conversion_function, conversion_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION(union_, simple_member_function, simple_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION(union_, member_variable, variables)
GENERATE_GET_MEMBERS_SPECIALIZATION(union_, bit_field, bit_fields)

GENERATE_GET_MEMBERS_SPECIALIZATION(member_union, member_class, classes)
GENERATE_GET_MEMBERS_SPECIALIZATION(member_union, member_union, unions)
GENERATE_GET_MEMBERS_SPECIALIZATION(member_union, member_enum, enums)
GENERATE_GET_MEMBERS_SPECIALIZATION(member_union, member_typedef, typedefs)
GENERATE_GET_MEMBERS_SPECIALIZATION(member_union, constructor, constructors)
GENERATE_GET_MEMBERS_SPECIALIZATION(member_union, destructor, get_destructor)
GENERATE_GET_MEMBERS_SPECIALIZATION(member_union, operator_member_function, operator_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION(member_union, conversion_function, conversion_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION(member_union, simple_member_function, simple_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION(member_union, member_variable, variables)
GENERATE_GET_MEMBERS_SPECIALIZATION(member_union, bit_field, bit_fields)

GENERATE_GET_MEMBERS_SPECIALIZATION(anonymous_union, member_class, classes)
GENERATE_GET_MEMBERS_SPECIALIZATION(anonymous_union, member_union, unions)
GENERATE_GET_MEMBERS_SPECIALIZATION(anonymous_union, member_enum, enums)
GENERATE_GET_MEMBERS_SPECIALIZATION(anonymous_union, member_typedef, typedefs)
GENERATE_GET_MEMBERS_SPECIALIZATION(anonymous_union, member_variable, variables)
GENERATE_GET_MEMBERS_SPECIALIZATION(anonymous_union, bit_field, bit_fields)

GENERATE_GET_MEMBERS_SPECIALIZATION(anonymous_member_union, member_class, classes)
GENERATE_GET_MEMBERS_SPECIALIZATION(anonymous_member_union, member_union, unions)
GENERATE_GET_MEMBERS_SPECIALIZATION(anonymous_member_union, member_enum, enums)
GENERATE_GET_MEMBERS_SPECIALIZATION(anonymous_member_union, member_typedef, typedefs)
GENERATE_GET_MEMBERS_SPECIALIZATION(anonymous_member_union, member_variable, variables)
GENERATE_GET_MEMBERS_SPECIALIZATION(anonymous_member_union, bit_field, bit_fields)

GENERATE_GET_MEMBERS_SPECIALIZATION(statement_block, namespace_alias, namespace_aliases)

#undef GENERATE_GET_MEMBERS_SPECIALIZATION

}}}}} //namespace scalpel::cpp::semantic_entities::generic_queries::detail

