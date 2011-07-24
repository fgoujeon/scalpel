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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SEMANTIC_ENTITY_ANALYSIS_GET_MEMBERS_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SEMANTIC_ENTITY_ANALYSIS_GET_MEMBERS_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/utility/single_object_range.hpp>
#include <scalpel/utility/single_object_const_range.hpp>
#include <scalpel/utility/unique_ptr_vector.hpp>
#include <vector>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace generic_queries { namespace detail
{

template<class DeclarativeRegion, class Entity, bool Const>
struct get_members_return_type;

template<class DeclarativeRegion, class Entity>
struct get_members_return_type<DeclarativeRegion, Entity, false>
{
	typedef typename utility::unique_ptr_vector<Entity>::range type;
};

template<class DeclarativeRegion, class Entity>
struct get_members_return_type<DeclarativeRegion, Entity, true>
{
	typedef const utility::unique_ptr_vector<Entity>& type;
};

template<class DeclarativeRegion>
struct get_members_return_type<DeclarativeRegion, semantic_entities::unnamed_namespace, false>
{
	typedef utility::single_object_range<semantic_entities::unnamed_namespace> type;
};

template<class DeclarativeRegion>
struct get_members_return_type<DeclarativeRegion, semantic_entities::unnamed_namespace, true>
{
	typedef utility::single_object_const_range<semantic_entities::unnamed_namespace> type;
};

template<>
struct get_members_return_type<semantic_entities::linked_unnamed_namespace, semantic_entities::linked_unnamed_namespace, false>
{
	typedef utility::single_object_range<semantic_entities::linked_unnamed_namespace> type;
};

template<>
struct get_members_return_type<semantic_entities::linked_unnamed_namespace, semantic_entities::linked_unnamed_namespace, true>
{
	typedef utility::single_object_const_range<semantic_entities::linked_unnamed_namespace> type;
};

template<class DeclarativeRegion>
struct get_members_return_type<DeclarativeRegion, semantic_entities::destructor, false>
{
	typedef utility::single_object_range<semantic_entities::destructor> type;
};

template<class DeclarativeRegion>
struct get_members_return_type<DeclarativeRegion, semantic_entities::destructor, true>
{
	typedef utility::single_object_const_range<semantic_entities::destructor> type;
};



#define GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(PARENT_TYPE) \
template<class Member> \
typename get_members_return_type<PARENT_TYPE, Member, false>::type \
get_members(semantic_entities::PARENT_TYPE& parent); \
 \
template<class Member> \
typename get_members_return_type<PARENT_TYPE, Member, true>::type \
get_members(const semantic_entities::PARENT_TYPE& parent);

GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(namespace_)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(linked_namespace)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(unnamed_namespace)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(linked_unnamed_namespace)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(class_)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(member_class)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(union_)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(member_union)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(anonymous_union)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(anonymous_member_union)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(constructor)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(destructor)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(operator_function)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(operator_member_function)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(conversion_function)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(simple_function)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(simple_member_function)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(statement_block)

#undef GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE



template<class, typename UnderlyingType>
typename get_members_return_type<basic_enum<UnderlyingType>, semantic_entities::enum_constant<UnderlyingType>, false>::type
get_members(semantic_entities::basic_enum<UnderlyingType>& parent)
{
	return parent.constants();
}

template<class, typename UnderlyingType>
typename get_members_return_type<basic_enum<UnderlyingType>, semantic_entities::enum_constant<UnderlyingType>, true>::type
get_members(const semantic_entities::basic_enum<UnderlyingType>& parent)
{
	return parent.constants();
}

template<class, typename UnderlyingType>
typename get_members_return_type<basic_member_enum<UnderlyingType>, semantic_entities::enum_constant<UnderlyingType>, false>::type
get_members(semantic_entities::basic_member_enum<UnderlyingType>& parent)
{
	return parent.constants();
}

template<class, typename UnderlyingType>
typename get_members_return_type<basic_member_enum<UnderlyingType>, semantic_entities::enum_constant<UnderlyingType>, true>::type
get_members(const semantic_entities::basic_member_enum<UnderlyingType>& parent)
{
	return parent.constants();
}

}}}}} //namespace scalpel::cpp::semantic_entities::generic_queries::detail

#endif

