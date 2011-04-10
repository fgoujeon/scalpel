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
#include <scalpel/utility/ptr_vector.hpp>
#include <vector>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace generic_queries { namespace detail
{

template<class Member, class DeclarativeRegion>
typename utility::vector_range<entity_alias<Member>>::type
get_entity_aliases(DeclarativeRegion& declarative_region);



//TODO should be const
extern std::vector<entity_alias<namespace_>> empty_namespace_ptr_vector;
extern std::vector<entity_alias<namespace_alias>> empty_namespace_alias_ptr_vector;
extern std::vector<entity_alias<class_>> empty_class_ptr_vector;
extern std::vector<entity_alias<member_class>> empty_member_class_ptr_vector;
extern std::vector<entity_alias<enum_>> empty_enum_ptr_vector;
extern std::vector<entity_alias<member_enum>> empty_member_enum_ptr_vector;
extern std::vector<entity_alias<typedef_>> empty_typedef_ptr_vector;
extern std::vector<entity_alias<member_typedef>> empty_member_typedef_ptr_vector;
extern std::vector<entity_alias<constructor>> empty_constructor_ptr_vector;
extern std::vector<entity_alias<destructor>> empty_destructor_ptr_vector;
extern std::vector<entity_alias<operator_member_function>> empty_operator_member_function_ptr_vector;
extern std::vector<entity_alias<conversion_function>> empty_conversion_function_ptr_vector;
extern std::vector<entity_alias<simple_member_function>> empty_simple_member_function_ptr_vector;
extern std::vector<entity_alias<operator_function>> empty_operator_function_ptr_vector;
extern std::vector<entity_alias<simple_function>> empty_simple_function_ptr_vector;
extern std::vector<entity_alias<variable>> empty_variable_ptr_vector;
extern std::vector<entity_alias<member_variable>> empty_member_variable_ptr_vector;
extern std::vector<entity_alias<bit_field>> empty_bit_field_ptr_vector;

template<class Member>
std::vector<entity_alias<Member>>&
get_empty_ptr_vector_of_type();

#define GET_EMPTY_PTR_VECTOR_OF_TYPE(MEMBER_TYPE, EMPTY_VECTOR) \
template<> \
inline \
std::vector<entity_alias<MEMBER_TYPE>>& \
get_empty_ptr_vector_of_type<MEMBER_TYPE>() \
{ \
	return EMPTY_VECTOR; \
}

GET_EMPTY_PTR_VECTOR_OF_TYPE(namespace_, empty_namespace_ptr_vector)
GET_EMPTY_PTR_VECTOR_OF_TYPE(namespace_alias, empty_namespace_alias_ptr_vector)
GET_EMPTY_PTR_VECTOR_OF_TYPE(class_, empty_class_ptr_vector)
GET_EMPTY_PTR_VECTOR_OF_TYPE(member_class, empty_member_class_ptr_vector)
GET_EMPTY_PTR_VECTOR_OF_TYPE(enum_, empty_enum_ptr_vector)
GET_EMPTY_PTR_VECTOR_OF_TYPE(member_enum, empty_member_enum_ptr_vector)
GET_EMPTY_PTR_VECTOR_OF_TYPE(typedef_, empty_typedef_ptr_vector)
GET_EMPTY_PTR_VECTOR_OF_TYPE(member_typedef, empty_member_typedef_ptr_vector)
GET_EMPTY_PTR_VECTOR_OF_TYPE(constructor, empty_constructor_ptr_vector)
GET_EMPTY_PTR_VECTOR_OF_TYPE(destructor, empty_destructor_ptr_vector)
GET_EMPTY_PTR_VECTOR_OF_TYPE(operator_member_function, empty_operator_member_function_ptr_vector)
GET_EMPTY_PTR_VECTOR_OF_TYPE(conversion_function, empty_conversion_function_ptr_vector)
GET_EMPTY_PTR_VECTOR_OF_TYPE(simple_member_function, empty_simple_member_function_ptr_vector)
GET_EMPTY_PTR_VECTOR_OF_TYPE(operator_function, empty_operator_function_ptr_vector)
GET_EMPTY_PTR_VECTOR_OF_TYPE(simple_function, empty_simple_function_ptr_vector)
GET_EMPTY_PTR_VECTOR_OF_TYPE(variable, empty_variable_ptr_vector)
GET_EMPTY_PTR_VECTOR_OF_TYPE(member_variable, empty_member_variable_ptr_vector)
GET_EMPTY_PTR_VECTOR_OF_TYPE(bit_field, empty_bit_field_ptr_vector)

#undef GET_EMPTY_PTR_VECTOR_OF_TYPE



template<class Member>
struct get_entity_aliases_impl;



//types of member that cannot be referred to by a using declaration

#define GENERATE_SPECIALIZATION(MEMBER_TYPE) \
template<> \
struct get_entity_aliases_impl<MEMBER_TYPE> \
{ \
	template<class DeclarativeRegion> \
	inline \
	static \
	typename utility::vector_range<entity_alias<MEMBER_TYPE>>::type \
	get(DeclarativeRegion&) \
	{ \
		return get_empty_ptr_vector_of_type<MEMBER_TYPE>(); \
	} \
};

GENERATE_SPECIALIZATION(namespace_)
GENERATE_SPECIALIZATION(unnamed_namespace)
GENERATE_SPECIALIZATION(namespace_alias)
GENERATE_SPECIALIZATION(constructor)
GENERATE_SPECIALIZATION(destructor)

#undef GENERATE_SPECIALIZATION



#define FOR(MEMBER_TYPE) \
template<> \
struct get_entity_aliases_impl<MEMBER_TYPE> \
{ \
	typedef MEMBER_TYPE member_t;

#define RETURN_NOTHING(DECLARATIVE_REGION_TYPE) \
	static \
	inline \
	typename utility::vector_range<entity_alias<member_t>>::type \
	get(DECLARATIVE_REGION_TYPE&) \
	{ \
		return get_empty_ptr_vector_of_type<member_t>(); \
	}

#define RETURN(DECLARATIVE_REGION_TYPE, MEMBER_FUNCTION) \
	static \
	inline \
	typename utility::vector_range<entity_alias<member_t>>::type \
	get(DECLARATIVE_REGION_TYPE& declarative_region) \
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
 \
	RETURN_NOTHING(enum_) \
	RETURN_NOTHING(member_enum) \
	RETURN_NOTHING(typedef_) \
	RETURN_NOTHING(member_typedef) \
	RETURN_NOTHING(constructor) \
	RETURN_NOTHING(destructor) \
	RETURN_NOTHING(operator_member_function) \
	RETURN_NOTHING(conversion_function) \
	RETURN_NOTHING(simple_member_function) \
	RETURN_NOTHING(operator_function) \
	RETURN_NOTHING(simple_function) \
};

FOR(class_)
	RETURN(namespace_, class_aliases)
	RETURN_NOTHING(linked_namespace)
	RETURN_NOTHING(unnamed_namespace)
	RETURN_NOTHING(linked_unnamed_namespace)
	RETURN_NOTHING(class_)
	RETURN_NOTHING(member_class)
	RETURN_NOTHING(statement_block)
END_FOR

FOR(member_class)
	RETURN_NOTHING(namespace_)
	RETURN_NOTHING(linked_namespace)
	RETURN_NOTHING(unnamed_namespace)
	RETURN_NOTHING(linked_unnamed_namespace)
	RETURN_NOTHING(class_)
	RETURN_NOTHING(member_class)
	RETURN_NOTHING(statement_block)
END_FOR

FOR(enum_)
	RETURN_NOTHING(namespace_)
	RETURN_NOTHING(linked_namespace)
	RETURN_NOTHING(unnamed_namespace)
	RETURN_NOTHING(linked_unnamed_namespace)
	RETURN_NOTHING(class_)
	RETURN_NOTHING(member_class)
	RETURN_NOTHING(statement_block)
END_FOR

FOR(member_enum)
	RETURN_NOTHING(namespace_)
	RETURN_NOTHING(linked_namespace)
	RETURN_NOTHING(unnamed_namespace)
	RETURN_NOTHING(linked_unnamed_namespace)
	RETURN_NOTHING(class_)
	RETURN_NOTHING(member_class)
	RETURN_NOTHING(statement_block)
END_FOR

FOR(typedef_)
	RETURN_NOTHING(namespace_)
	RETURN_NOTHING(linked_namespace)
	RETURN_NOTHING(unnamed_namespace)
	RETURN_NOTHING(linked_unnamed_namespace)
	RETURN_NOTHING(class_)
	RETURN_NOTHING(member_class)
	RETURN_NOTHING(statement_block)
END_FOR

FOR(member_typedef)
	RETURN_NOTHING(namespace_)
	RETURN_NOTHING(linked_namespace)
	RETURN_NOTHING(unnamed_namespace)
	RETURN_NOTHING(linked_unnamed_namespace)
	RETURN_NOTHING(class_)
	RETURN_NOTHING(member_class)
	RETURN_NOTHING(statement_block)
END_FOR

FOR(operator_member_function)
	RETURN_NOTHING(namespace_)
	RETURN_NOTHING(linked_namespace)
	RETURN_NOTHING(unnamed_namespace)
	RETURN_NOTHING(linked_unnamed_namespace)
	RETURN_NOTHING(class_)
	RETURN_NOTHING(member_class)
	RETURN_NOTHING(statement_block)
END_FOR

FOR(conversion_function)
	RETURN_NOTHING(namespace_)
	RETURN_NOTHING(linked_namespace)
	RETURN_NOTHING(unnamed_namespace)
	RETURN_NOTHING(linked_unnamed_namespace)
	RETURN_NOTHING(class_)
	RETURN_NOTHING(member_class)
	RETURN_NOTHING(statement_block)
END_FOR

FOR(simple_member_function)
	RETURN_NOTHING(namespace_)
	RETURN_NOTHING(linked_namespace)
	RETURN_NOTHING(unnamed_namespace)
	RETURN_NOTHING(linked_unnamed_namespace)
	RETURN_NOTHING(class_)
	RETURN_NOTHING(member_class)
	RETURN_NOTHING(statement_block)
END_FOR

FOR(operator_function)
	RETURN_NOTHING(namespace_)
	RETURN_NOTHING(linked_namespace)
	RETURN_NOTHING(unnamed_namespace)
	RETURN_NOTHING(linked_unnamed_namespace)
	RETURN_NOTHING(class_)
	RETURN_NOTHING(member_class)
	RETURN_NOTHING(statement_block)
END_FOR

FOR(simple_function)
	RETURN_NOTHING(namespace_)
	RETURN_NOTHING(linked_namespace)
	RETURN_NOTHING(unnamed_namespace)
	RETURN_NOTHING(linked_unnamed_namespace)
	RETURN_NOTHING(class_)
	RETURN_NOTHING(member_class)
	RETURN_NOTHING(statement_block)
END_FOR

FOR(variable)
	RETURN(namespace_, variable_aliases)
	RETURN_NOTHING(linked_namespace)
	RETURN_NOTHING(unnamed_namespace)
	RETURN_NOTHING(linked_unnamed_namespace)
	RETURN_NOTHING(class_)
	RETURN_NOTHING(member_class)
	RETURN_NOTHING(statement_block)
END_FOR

FOR(member_variable)
	RETURN_NOTHING(namespace_)
	RETURN_NOTHING(linked_namespace)
	RETURN_NOTHING(unnamed_namespace)
	RETURN_NOTHING(linked_unnamed_namespace)
	RETURN_NOTHING(class_)
	RETURN_NOTHING(member_class)
	RETURN_NOTHING(statement_block)
END_FOR

FOR(bit_field)
	RETURN_NOTHING(namespace_)
	RETURN_NOTHING(linked_namespace)
	RETURN_NOTHING(unnamed_namespace)
	RETURN_NOTHING(linked_unnamed_namespace)
	RETURN_NOTHING(class_)
	RETURN_NOTHING(member_class)
	RETURN_NOTHING(statement_block)
END_FOR

#undef FOR
#undef END_FOR
#undef RETURN_NOTHING



//main overload
template<class Member, class DeclarativeRegion>
inline
typename utility::vector_range<entity_alias<Member>>::type
get_entity_aliases(DeclarativeRegion& declarative_region)
{
	return get_entity_aliases_impl<Member>::get(declarative_region);
}



//overload for declarative region variants
template<class Member>
struct get_entity_aliases_visitor: public utility::static_visitor<typename utility::vector_range<entity_alias<Member>>::type>
{
	template<class DeclarativeRegion>
	inline
	typename utility::vector_range<entity_alias<Member>>::type
	operator()(DeclarativeRegion* declarative_region) const
	{
		return get_entity_aliases<Member, DeclarativeRegion>(*declarative_region);
	}
};

template<class Member, class... DeclarativeRegions>
inline
typename utility::vector_range<entity_alias<Member>>::type
get_entity_aliases(utility::variant<DeclarativeRegions...>& declarative_region)
{
	get_entity_aliases_visitor<Member> visitor;
	return apply_visitor(visitor, declarative_region);
}

}}}}} //namespace scalpel::cpp::semantic_entities::generic_queries::detail

#endif

