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

//TODO these empty containers should be const

template<class Entity>
struct empty_result
{
	typedef utility::unique_ptr_vector<Entity> type;
	static type value;
};

template<class Entity>
typename empty_result<Entity>::type
	empty_result<Entity>::value
;

template<>
struct empty_result<semantic_entities::destructor>
{
	typedef utility::single_object_range<semantic_entities::destructor> type;
	static type value;
};

typename empty_result<semantic_entities::destructor>::type
	empty_result<semantic_entities::destructor>::value
;



#define GENERATE_NON_CONST_GET_MEMBERS_SPECIALIZATION(PARENT_TYPE, MEMBER_TYPE, PARENT_MEMBER_FUNCTION) \
template<> \
get_members_return_type<semantic_entities::MEMBER_TYPE, false>::type \
get_members<semantic_entities::MEMBER_TYPE>(semantic_entities::PARENT_TYPE& parent) \
{ \
	return parent.PARENT_MEMBER_FUNCTION(); \
}

#define GENERATE_GET_MEMBERS_SPECIALIZATION(PARENT_TYPE, MEMBER_TYPE, PARENT_MEMBER_FUNCTION) \
GENERATE_NON_CONST_GET_MEMBERS_SPECIALIZATION(PARENT_TYPE, MEMBER_TYPE, PARENT_MEMBER_FUNCTION) \
 \
template<> \
get_members_return_type<semantic_entities::MEMBER_TYPE, true>::type \
get_members<semantic_entities::MEMBER_TYPE>(const semantic_entities::PARENT_TYPE& parent) \
{ \
	return parent.PARENT_MEMBER_FUNCTION(); \
}

#define GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(PARENT_TYPE, MEMBER_TYPE) \
template<> \
get_members_return_type<semantic_entities::MEMBER_TYPE, false>::type \
get_members<semantic_entities::MEMBER_TYPE>(semantic_entities::PARENT_TYPE&) \
{ \
	return empty_result<semantic_entities::MEMBER_TYPE>::value; \
} \
 \
template<> \
get_members_return_type<semantic_entities::MEMBER_TYPE, true>::type \
get_members<semantic_entities::MEMBER_TYPE>(const semantic_entities::PARENT_TYPE&) \
{ \
	return empty_result<semantic_entities::MEMBER_TYPE>::value; \
}



GENERATE_GET_MEMBERS_SPECIALIZATION          (namespace_, namespace_, namespaces)
//GENERATE_GET_MEMBERS_SPECIALIZATION          (namespace_, unnamed_namespace, get_unnamed_namespace)
GENERATE_GET_MEMBERS_SPECIALIZATION          (namespace_, class_, classes)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (namespace_, member_class)
GENERATE_GET_MEMBERS_SPECIALIZATION          (namespace_, enum_, enums)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (namespace_, member_enum)
GENERATE_GET_MEMBERS_SPECIALIZATION          (namespace_, typedef_, typedefs)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (namespace_, member_typedef)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (namespace_, constructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (namespace_, destructor)
GENERATE_GET_MEMBERS_SPECIALIZATION          (namespace_, operator_function, operator_functions)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (namespace_, operator_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (namespace_, conversion_function)
GENERATE_GET_MEMBERS_SPECIALIZATION          (namespace_, simple_function, simple_functions)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (namespace_, simple_member_function)
GENERATE_GET_MEMBERS_SPECIALIZATION          (namespace_, variable, variables)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (namespace_, member_variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (namespace_, bit_field)
GENERATE_GET_MEMBERS_SPECIALIZATION          (namespace_, namespace_alias, namespace_aliases)

GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (linked_namespace, namespace_)
//GENERATE_GET_MEMBERS_SPECIALIZATION          (linked_namespace, unnamed_namespace, get_unnamed_namespace)
GENERATE_GET_MEMBERS_SPECIALIZATION          (linked_namespace, class_, classes)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (linked_namespace, member_class)
GENERATE_GET_MEMBERS_SPECIALIZATION          (linked_namespace, enum_, enums)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (linked_namespace, member_enum)
GENERATE_GET_MEMBERS_SPECIALIZATION          (linked_namespace, typedef_, typedefs)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (linked_namespace, member_typedef)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (linked_namespace, constructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (linked_namespace, destructor)
GENERATE_GET_MEMBERS_SPECIALIZATION          (linked_namespace, operator_function, operator_functions)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (linked_namespace, operator_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (linked_namespace, conversion_function)
GENERATE_GET_MEMBERS_SPECIALIZATION          (linked_namespace, simple_function, simple_functions)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (linked_namespace, simple_member_function)
GENERATE_GET_MEMBERS_SPECIALIZATION          (linked_namespace, variable, variables)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (linked_namespace, member_variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (linked_namespace, bit_field)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (linked_namespace, namespace_alias)

GENERATE_GET_MEMBERS_SPECIALIZATION          (unnamed_namespace, namespace_, namespaces)
//GENERATE_GET_MEMBERS_SPECIALIZATION          (unnamed_namespace, unnamed_namespace, get_unnamed_namespace)
GENERATE_GET_MEMBERS_SPECIALIZATION          (unnamed_namespace, class_, classes)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (unnamed_namespace, member_class)
GENERATE_GET_MEMBERS_SPECIALIZATION          (unnamed_namespace, enum_, enums)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (unnamed_namespace, member_enum)
GENERATE_GET_MEMBERS_SPECIALIZATION          (unnamed_namespace, typedef_, typedefs)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (unnamed_namespace, member_typedef)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (unnamed_namespace, constructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (unnamed_namespace, destructor)
GENERATE_GET_MEMBERS_SPECIALIZATION          (unnamed_namespace, operator_function, operator_functions)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (unnamed_namespace, operator_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (unnamed_namespace, conversion_function)
GENERATE_GET_MEMBERS_SPECIALIZATION          (unnamed_namespace, simple_function, simple_functions)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (unnamed_namespace, simple_member_function)
GENERATE_GET_MEMBERS_SPECIALIZATION          (unnamed_namespace, variable, variables)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (unnamed_namespace, member_variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (unnamed_namespace, bit_field)
GENERATE_GET_MEMBERS_SPECIALIZATION          (unnamed_namespace, namespace_alias, namespace_aliases)

GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (linked_unnamed_namespace, namespace_)
//GENERATE_GET_MEMBERS_SPECIALIZATION          (linked_unnamed_namespace, unnamed_namespace, get_unnamed_namespace)
GENERATE_GET_MEMBERS_SPECIALIZATION          (linked_unnamed_namespace, class_, classes)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (linked_unnamed_namespace, member_class)
GENERATE_GET_MEMBERS_SPECIALIZATION          (linked_unnamed_namespace, enum_, enums)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (linked_unnamed_namespace, member_enum)
GENERATE_GET_MEMBERS_SPECIALIZATION          (linked_unnamed_namespace, typedef_, typedefs)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (linked_unnamed_namespace, member_typedef)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (linked_unnamed_namespace, constructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (linked_unnamed_namespace, destructor)
GENERATE_GET_MEMBERS_SPECIALIZATION          (linked_unnamed_namespace, operator_function, operator_functions)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (linked_unnamed_namespace, operator_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (linked_unnamed_namespace, conversion_function)
GENERATE_GET_MEMBERS_SPECIALIZATION          (linked_unnamed_namespace, simple_function, simple_functions)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (linked_unnamed_namespace, simple_member_function)
GENERATE_GET_MEMBERS_SPECIALIZATION          (linked_unnamed_namespace, variable, variables)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (linked_unnamed_namespace, member_variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (linked_unnamed_namespace, bit_field)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (linked_unnamed_namespace, namespace_alias)

GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (class_, namespace_)
//GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (class_, unnamed_namespace)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (class_, class_)
GENERATE_GET_MEMBERS_SPECIALIZATION          (class_, member_class, classes)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (class_, enum_)
GENERATE_GET_MEMBERS_SPECIALIZATION          (class_, member_enum, enums)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (class_, typedef_)
GENERATE_GET_MEMBERS_SPECIALIZATION          (class_, member_typedef, typedefs)
GENERATE_GET_MEMBERS_SPECIALIZATION          (class_, constructor, constructors)
GENERATE_GET_MEMBERS_SPECIALIZATION          (class_, destructor, get_destructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (class_, operator_function)
GENERATE_GET_MEMBERS_SPECIALIZATION          (class_, operator_member_function, operator_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION          (class_, conversion_function, conversion_functions)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (class_, simple_function)
GENERATE_GET_MEMBERS_SPECIALIZATION          (class_, simple_member_function, simple_functions)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (class_, variable)
GENERATE_GET_MEMBERS_SPECIALIZATION          (class_, member_variable, variables)
GENERATE_GET_MEMBERS_SPECIALIZATION          (class_, bit_field, bit_fields)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (class_, namespace_alias)

GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (member_class, namespace_)
//GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (member_class, unnamed_namespace)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (member_class, class_)
GENERATE_GET_MEMBERS_SPECIALIZATION          (member_class, member_class, classes)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (member_class, enum_)
GENERATE_GET_MEMBERS_SPECIALIZATION          (member_class, member_enum, enums)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (member_class, typedef_)
GENERATE_GET_MEMBERS_SPECIALIZATION          (member_class, member_typedef, typedefs)
GENERATE_GET_MEMBERS_SPECIALIZATION          (member_class, constructor, constructors)
GENERATE_GET_MEMBERS_SPECIALIZATION          (member_class, destructor, get_destructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (member_class, operator_function)
GENERATE_GET_MEMBERS_SPECIALIZATION          (member_class, operator_member_function, operator_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION          (member_class, conversion_function, conversion_functions)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (member_class, simple_function)
GENERATE_GET_MEMBERS_SPECIALIZATION          (member_class, simple_member_function, simple_functions)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (member_class, variable)
GENERATE_GET_MEMBERS_SPECIALIZATION          (member_class, member_variable, variables)
GENERATE_GET_MEMBERS_SPECIALIZATION          (member_class, bit_field, bit_fields)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (member_class, namespace_alias)

GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (constructor, namespace_)
//GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (constructor, unnamed_namespace)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (constructor, class_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (constructor, member_class)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (constructor, enum_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (constructor, member_enum)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (constructor, typedef_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (constructor, member_typedef)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (constructor, constructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (constructor, destructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (constructor, operator_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (constructor, operator_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (constructor, conversion_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (constructor, simple_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (constructor, simple_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (constructor, variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (constructor, member_variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (constructor, bit_field)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (constructor, namespace_alias)

GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (destructor, namespace_)
//GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (destructor, unnamed_namespace)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (destructor, class_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (destructor, member_class)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (destructor, enum_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (destructor, member_enum)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (destructor, typedef_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (destructor, member_typedef)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (destructor, constructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (destructor, destructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (destructor, operator_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (destructor, operator_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (destructor, conversion_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (destructor, simple_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (destructor, simple_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (destructor, variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (destructor, member_variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (destructor, bit_field)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (destructor, namespace_alias)

GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_function, namespace_)
//GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_function, unnamed_namespace)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_function, class_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_function, member_class)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_function, enum_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_function, member_enum)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_function, typedef_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_function, member_typedef)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_function, constructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_function, destructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_function, operator_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_function, operator_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_function, conversion_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_function, simple_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_function, simple_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_function, variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_function, member_variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_function, bit_field)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_function, namespace_alias)

GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_member_function, namespace_)
//GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_member_function, unnamed_namespace)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_member_function, class_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_member_function, member_class)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_member_function, enum_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_member_function, member_enum)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_member_function, typedef_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_member_function, member_typedef)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_member_function, constructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_member_function, destructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_member_function, operator_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_member_function, operator_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_member_function, conversion_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_member_function, simple_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_member_function, simple_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_member_function, variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_member_function, member_variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_member_function, bit_field)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (operator_member_function, namespace_alias)

GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (conversion_function, namespace_)
//GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (conversion_function, unnamed_namespace)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (conversion_function, class_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (conversion_function, member_class)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (conversion_function, enum_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (conversion_function, member_enum)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (conversion_function, typedef_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (conversion_function, member_typedef)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (conversion_function, constructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (conversion_function, destructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (conversion_function, operator_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (conversion_function, operator_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (conversion_function, conversion_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (conversion_function, simple_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (conversion_function, simple_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (conversion_function, variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (conversion_function, member_variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (conversion_function, bit_field)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (conversion_function, namespace_alias)

GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_function, namespace_)
//GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_function, unnamed_namespace)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_function, class_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_function, member_class)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_function, enum_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_function, member_enum)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_function, typedef_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_function, member_typedef)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_function, constructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_function, destructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_function, operator_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_function, operator_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_function, conversion_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_function, simple_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_function, simple_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_function, variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_function, member_variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_function, bit_field)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_function, namespace_alias)

GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_member_function, namespace_)
//GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_member_function, unnamed_namespace)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_member_function, class_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_member_function, member_class)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_member_function, enum_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_member_function, member_enum)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_member_function, typedef_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_member_function, member_typedef)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_member_function, constructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_member_function, destructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_member_function, operator_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_member_function, operator_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_member_function, conversion_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_member_function, simple_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_member_function, simple_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_member_function, variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_member_function, member_variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_member_function, bit_field)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (simple_member_function, namespace_alias)

GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (statement_block, namespace_)
//GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (statement_block, unnamed_namespace)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (statement_block, class_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (statement_block, member_class)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (statement_block, enum_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (statement_block, member_enum)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (statement_block, typedef_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (statement_block, member_typedef)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (statement_block, constructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (statement_block, destructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (statement_block, operator_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (statement_block, operator_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (statement_block, conversion_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (statement_block, simple_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (statement_block, simple_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (statement_block, variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (statement_block, member_variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION    (statement_block, bit_field)
GENERATE_GET_MEMBERS_SPECIALIZATION          (statement_block, namespace_alias, namespace_aliases)

}}}}} //namespace scalpel::cpp::semantic_entities::generic_queries::detail

