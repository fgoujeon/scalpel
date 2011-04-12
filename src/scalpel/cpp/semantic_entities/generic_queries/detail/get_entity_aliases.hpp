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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SEMANTIC_ENTITY_ANALYSIS_GET_ENTITY_ALIASES_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SEMANTIC_ENTITY_ANALYSIS_GET_ENTITY_ALIASES_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/utility/vector_range.hpp>
#include <vector>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace generic_queries { namespace detail
{

template<class Member>
struct get_entity_aliases_impl;

#define FOR(MEMBER_TYPE) \
template<> \
struct get_entity_aliases_impl<MEMBER_TYPE> \
{ \
	typedef MEMBER_TYPE member_t;

#define RETURN(DECLARATIVE_REGION_TYPE, MEMBER_FUNCTION) \
	static \
	inline \
	typename utility::vector_range<entity_alias<member_t>>::type \
	get(DECLARATIVE_REGION_TYPE& declarative_region) \
	{ \
		return declarative_region.MEMBER_FUNCTION(); \
	} \
 \
	static \
	inline \
	const std::vector<entity_alias<member_t>>& \
	get(const DECLARATIVE_REGION_TYPE& declarative_region) \
	{ \
		return declarative_region.MEMBER_FUNCTION(); \
	}

#define END_FOR \
	static \
	inline \
	typename utility::vector_range<entity_alias<member_t>>::type \
	get(namespace_alias& declarative_region) \
	{ \
		return get(declarative_region.referred_namespace()); \
	} \
};

FOR(class_)
	RETURN(namespace_, class_aliases)
	RETURN(linked_namespace, class_aliases)
	RETURN(unnamed_namespace, class_aliases)
	RETURN(linked_unnamed_namespace, class_aliases)
END_FOR

FOR(enum_)
	RETURN(namespace_, enum_aliases)
	RETURN(linked_namespace, enum_aliases)
	RETURN(unnamed_namespace, enum_aliases)
	RETURN(linked_unnamed_namespace, enum_aliases)
END_FOR

FOR(typedef_)
	RETURN(namespace_, typedef_aliases)
	RETURN(linked_namespace, typedef_aliases)
	RETURN(unnamed_namespace, typedef_aliases)
	RETURN(linked_unnamed_namespace, typedef_aliases)
END_FOR

FOR(operator_function)
	RETURN(namespace_, operator_function_aliases)
	RETURN(linked_namespace, operator_function_aliases)
	RETURN(unnamed_namespace, operator_function_aliases)
	RETURN(linked_unnamed_namespace, operator_function_aliases)
END_FOR

FOR(simple_function)
	RETURN(namespace_, simple_function_aliases)
	RETURN(linked_namespace, simple_function_aliases)
	RETURN(unnamed_namespace, simple_function_aliases)
	RETURN(linked_unnamed_namespace, simple_function_aliases)
END_FOR

FOR(variable)
	RETURN(namespace_, variable_aliases)
	RETURN(linked_namespace, variable_aliases)
	RETURN(unnamed_namespace, variable_aliases)
	RETURN(linked_unnamed_namespace, variable_aliases)
END_FOR

#undef FOR
#undef RETURN
#undef END_FOR



template<class Member, class DeclarativeRegion>
inline
typename utility::vector_range<entity_alias<Member>>::type
get_entity_aliases(DeclarativeRegion& declarative_region)
{
	return get_entity_aliases_impl<Member>::get(declarative_region);
}

template<class Member, class DeclarativeRegion>
inline
const std::vector<entity_alias<Member>>&
get_entity_aliases(const DeclarativeRegion& declarative_region)
{
	return get_entity_aliases_impl<Member>::get(declarative_region);
}

}}}}} //namespace scalpel::cpp::semantic_entities::generic_queries::detail

#endif

