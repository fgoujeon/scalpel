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

#ifndef SCALPEL_CPP_LINKAGE_DETAIL_ENTITY_GROUPS_HPP
#define SCALPEL_CPP_LINKAGE_DETAIL_ENTITY_GROUPS_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <vector>
#include <map>

namespace scalpel { namespace cpp { namespace linkage { namespace detail
{

template<class Entity>
struct entity_groups_of_type
{
	typedef std::map<std::string, std::vector<const Entity*>> type;
};

struct entity_groups
{
	std::vector<const semantic_entities::namespace_*> global_namespaces;



	//
	//entities with external linkage
	//

	typename entity_groups_of_type<semantic_entities::namespace_>::type namespaces;
	typename entity_groups_of_type<semantic_entities::class_>::type classes;
	typename entity_groups_of_type<semantic_entities::member_class>::type member_classes;
	typename entity_groups_of_type<semantic_entities::union_>::type unions;
	typename entity_groups_of_type<semantic_entities::member_union>::type member_unions;
	typename entity_groups_of_type<semantic_entities::enum_>::type enums;
	typename entity_groups_of_type<semantic_entities::member_enum>::type member_enums;
	typename entity_groups_of_type<semantic_entities::typedef_>::type typedefs;
	typename entity_groups_of_type<semantic_entities::member_typedef>::type member_typedefs;
	typename entity_groups_of_type<semantic_entities::constructor>::type constructors;
	typename entity_groups_of_type<semantic_entities::destructor>::type destructors;
	typename entity_groups_of_type<semantic_entities::operator_member_function>::type operator_member_functions;
	typename entity_groups_of_type<semantic_entities::conversion_function>::type conversion_functions;
	typename entity_groups_of_type<semantic_entities::simple_member_function>::type simple_member_functions;
	typename entity_groups_of_type<semantic_entities::operator_function>::type operator_functions;
	typename entity_groups_of_type<semantic_entities::simple_function>::type simple_functions;
	typename entity_groups_of_type<semantic_entities::variable>::type variables;
	typename entity_groups_of_type<semantic_entities::member_variable>::type member_variables;
	typename entity_groups_of_type<semantic_entities::static_member_variable>::type static_member_variables;
	typename entity_groups_of_type<semantic_entities::bit_field>::type bit_fields;
	typename entity_groups_of_type<semantic_entities::enum_constant<int>>::type int_enum_constants;
	typename entity_groups_of_type<semantic_entities::enum_constant<unsigned int>>::type unsigned_int_enum_constants;
	typename entity_groups_of_type<semantic_entities::enum_constant<long int>>::type long_int_enum_constants;
	typename entity_groups_of_type<semantic_entities::enum_constant<unsigned long int>>::type unsigned_long_int_enum_constants;



	//
	//entities with internal linkage
	//

	std::vector<const semantic_entities::namespace_*> internal_namespaces;
	std::vector<const semantic_entities::unnamed_namespace*> internal_unnamed_namespaces;
	std::vector<const semantic_entities::class_*> internal_classes;
	std::vector<const semantic_entities::member_class*> internal_member_classes;
	std::vector<const semantic_entities::union_*> internal_unions;
	std::vector<const semantic_entities::member_union*> internal_member_unions;
	std::vector<const semantic_entities::anonymous_union*> internal_anonymous_unions;
	std::vector<const semantic_entities::anonymous_member_union*> internal_anonymous_member_unions;
	std::vector<const semantic_entities::enum_*> internal_enums;
	std::vector<const semantic_entities::member_enum*> internal_member_enums;
	std::vector<const semantic_entities::typedef_*> internal_typedefs;
	std::vector<const semantic_entities::member_typedef*> internal_member_typedefs;
	std::vector<const semantic_entities::constructor*> internal_constructors;
	std::vector<const semantic_entities::destructor*> internal_destructors;
	std::vector<const semantic_entities::operator_member_function*> internal_operator_member_functions;
	std::vector<const semantic_entities::conversion_function*> internal_conversion_functions;
	std::vector<const semantic_entities::simple_member_function*> internal_simple_member_functions;
	std::vector<const semantic_entities::operator_function*> internal_operator_functions;
	std::vector<const semantic_entities::simple_function*> internal_simple_functions;
	std::vector<const semantic_entities::variable*> internal_variables;
	std::vector<const semantic_entities::member_variable*> internal_member_variables;
	std::vector<const semantic_entities::static_member_variable*> internal_static_member_variables;
	std::vector<const semantic_entities::bit_field*> internal_bit_fields;
	std::vector<const semantic_entities::enum_constant<int>*> internal_int_enum_constants;
	std::vector<const semantic_entities::enum_constant<unsigned int>*> internal_unsigned_int_enum_constants;
	std::vector<const semantic_entities::enum_constant<long int>*> internal_long_int_enum_constants;
	std::vector<const semantic_entities::enum_constant<unsigned long int>*> internal_unsigned_long_int_enum_constants;

	template<class Entity>
	std::vector<const Entity*>&
	internal_entities_of_type();

	template<class Entity>
	const std::vector<const Entity*>&
	internal_entities_of_type() const;
};

template<class Entity>
typename entity_groups_of_type<Entity>::type&
get_entity_groups_of_type(entity_groups& n);

template<class Entity>
const typename entity_groups_of_type<Entity>::type&
get_entity_groups_of_type(const entity_groups& n);

}}}} //namespace scalpel::cpp::linkage::detail

#endif

