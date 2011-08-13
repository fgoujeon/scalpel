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

template<class DeclarativeRegion, class Entity, bool Const>
struct get_entity_aliases_return_type;

template<class DeclarativeRegion, class Entity>
struct get_entity_aliases_return_type<DeclarativeRegion, Entity, false>
{
	typedef typename utility::vector_range<entity_alias<Entity>>::type type;
};

template<class DeclarativeRegion, class Entity>
struct get_entity_aliases_return_type<DeclarativeRegion, Entity, true>
{
	typedef const std::vector<entity_alias<Entity>>& type;
};

template<class Entity>
struct get_entity_aliases_return_type<class_, Entity, false>
{
	typedef typename utility::vector_range<member_entity_alias<Entity>>::type type;
};

template<class Entity>
struct get_entity_aliases_return_type<class_, Entity, true>
{
	typedef const std::vector<member_entity_alias<Entity>>& type;
};

template<class Entity>
struct get_entity_aliases_return_type<member_class, Entity, false>
{
	typedef typename utility::vector_range<member_entity_alias<Entity>>::type type;
};

template<class Entity>
struct get_entity_aliases_return_type<member_class, Entity, true>
{
	typedef const std::vector<member_entity_alias<Entity>>& type;
};



template<class Entity>
struct get_entity_aliases_impl;

#define FOR(MEMBER_TYPE) \
template<> \
struct get_entity_aliases_impl<MEMBER_TYPE> \
{ \
	typedef MEMBER_TYPE member_t;

#define RETURN_ENTITY_ALIASES(DECLARATIVE_REGION_TYPE, MEMBER_FUNCTION) \
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

#define RETURN_MEMBER_ENTITY_ALIASES(DECLARATIVE_REGION_TYPE, MEMBER_FUNCTION) \
	static \
	inline \
	typename utility::vector_range<member_entity_alias<member_t>>::type \
	get(DECLARATIVE_REGION_TYPE& declarative_region) \
	{ \
		return declarative_region.MEMBER_FUNCTION(); \
	} \
 \
	static \
	inline \
	const std::vector<member_entity_alias<member_t>>& \
	get(const DECLARATIVE_REGION_TYPE& declarative_region) \
	{ \
		return declarative_region.MEMBER_FUNCTION(); \
	}

#define END_FOR \
};

FOR(class_)
	RETURN_ENTITY_ALIASES(namespace_, class_aliases)
	RETURN_ENTITY_ALIASES(unnamed_namespace, class_aliases)
END_FOR

FOR(member_class)
	RETURN_MEMBER_ENTITY_ALIASES(class_, class_aliases)
	RETURN_MEMBER_ENTITY_ALIASES(member_class, class_aliases)
END_FOR

FOR(enum_)
	RETURN_ENTITY_ALIASES(namespace_, enum_aliases)
	RETURN_ENTITY_ALIASES(unnamed_namespace, enum_aliases)
END_FOR

FOR(member_enum)
	RETURN_MEMBER_ENTITY_ALIASES(class_, enum_aliases)
	RETURN_MEMBER_ENTITY_ALIASES(member_class, enum_aliases)
END_FOR

FOR(typedef_)
	RETURN_ENTITY_ALIASES(namespace_, typedef_aliases)
	RETURN_ENTITY_ALIASES(unnamed_namespace, typedef_aliases)
END_FOR

FOR(member_typedef)
	RETURN_MEMBER_ENTITY_ALIASES(class_, typedef_aliases)
	RETURN_MEMBER_ENTITY_ALIASES(member_class, typedef_aliases)
END_FOR

FOR(operator_member_function)
	RETURN_MEMBER_ENTITY_ALIASES(class_, operator_function_aliases)
	RETURN_MEMBER_ENTITY_ALIASES(member_class, operator_function_aliases)
END_FOR

FOR(conversion_function)
	RETURN_MEMBER_ENTITY_ALIASES(class_, conversion_function_aliases)
	RETURN_MEMBER_ENTITY_ALIASES(member_class, conversion_function_aliases)
END_FOR

FOR(simple_member_function)
	RETURN_MEMBER_ENTITY_ALIASES(class_, simple_function_aliases)
	RETURN_MEMBER_ENTITY_ALIASES(member_class, simple_function_aliases)
END_FOR

FOR(operator_function)
	RETURN_ENTITY_ALIASES(namespace_, operator_function_aliases)
	RETURN_ENTITY_ALIASES(unnamed_namespace, operator_function_aliases)
END_FOR

FOR(simple_function)
	RETURN_ENTITY_ALIASES(namespace_, simple_function_aliases)
	RETURN_ENTITY_ALIASES(unnamed_namespace, simple_function_aliases)
END_FOR

FOR(variable)
	RETURN_ENTITY_ALIASES(namespace_, variable_aliases)
	RETURN_ENTITY_ALIASES(unnamed_namespace, variable_aliases)
END_FOR

FOR(member_variable)
	RETURN_MEMBER_ENTITY_ALIASES(class_, variable_aliases)
	RETURN_MEMBER_ENTITY_ALIASES(member_class, variable_aliases)
END_FOR

FOR(static_member_variable)
	RETURN_MEMBER_ENTITY_ALIASES(class_, static_variable_aliases)
	RETURN_MEMBER_ENTITY_ALIASES(member_class, static_variable_aliases)
END_FOR

FOR(bit_field)
	RETURN_MEMBER_ENTITY_ALIASES(class_, bit_field_aliases)
	RETURN_MEMBER_ENTITY_ALIASES(member_class, bit_field_aliases)
END_FOR

#undef FOR
#undef RETURN_ENTITY_ALIASES
#undef RETURN_MEMBER_ENTITY_ALIASES
#undef END_FOR



template<class Entity, class DeclarativeRegion>
inline
typename get_entity_aliases_return_type<DeclarativeRegion, Entity, false>::type
get_entity_aliases(DeclarativeRegion& declarative_region)
{
	return get_entity_aliases_impl<Entity>::get(declarative_region);
}

template<class Entity, class DeclarativeRegion>
inline
typename get_entity_aliases_return_type<DeclarativeRegion, Entity, true>::type
get_entity_aliases(const DeclarativeRegion& declarative_region)
{
	return get_entity_aliases_impl<Entity>::get(declarative_region);
}

}}}}} //namespace scalpel::cpp::semantic_entities::generic_queries::detail

#endif

