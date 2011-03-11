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

#ifndef SCALPEL_CPP_LINKING_DETAIL_ENTITY_GROUPS_HPP
#define SCALPEL_CPP_LINKING_DETAIL_ENTITY_GROUPS_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <vector>
#include <map>

namespace scalpel { namespace cpp { namespace linking { namespace detail
{

template<class Entity>
struct entity_groups_of_type
{
	typedef std::map<std::string, std::vector<const Entity*>> type;
};

struct entity_groups
{
	typename entity_groups_of_type<semantic_entities::namespace_>::type namespaces;
	typename entity_groups_of_type<semantic_entities::class_>::type classes;
	typename entity_groups_of_type<semantic_entities::member_class>::type member_classes;
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
};

template<class Entity>
typename entity_groups_of_type<Entity>::type&
get_entity_groups_of_type(entity_groups& n);

template<class Entity>
const typename entity_groups_of_type<Entity>::type&
get_entity_groups_of_type(const entity_groups& n);

}}}} //namespace scalpel::cpp::linking::detail

#endif

