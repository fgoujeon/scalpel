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

#ifndef SCALPEL_CPP_LINKAGE_DETAIL_FINAL_GRAPH_ENTITIES_HPP
#define SCALPEL_CPP_LINKAGE_DETAIL_FINAL_GRAPH_ENTITIES_HPP

#include "linked_type.hpp"
#include <scalpel/cpp/semantic_graph.hpp>
#include <map>
#include <vector>

namespace scalpel { namespace cpp { namespace linkage { namespace detail
{

template<class Entity>
struct old_and_new_entity_pair
{
	const Entity* old_entity;
	Entity* new_entity;
};

struct final_graph_entities
{
	template<class Entity>
	std::map<const typename nonlinked_type<Entity>::type*, Entity*>&
	get_map_of_linked_type();

	template<class Entity>
	const std::map<const typename nonlinked_type<Entity>::type*, Entity*>&
	get_map_of_linked_type() const;

	std::unique_ptr<semantic_entities::linked_namespace> global_namespace;
	std::map<const semantic_entities::namespace_*, semantic_entities::linked_namespace*> namespaces;
	std::map<const semantic_entities::unnamed_namespace*, semantic_entities::linked_unnamed_namespace*> unnamed_namespaces;
	std::map<const semantic_entities::class_*, semantic_entities::class_*> classes;
	std::map<const semantic_entities::member_class*, semantic_entities::member_class*> member_classes;
	std::map<const semantic_entities::union_*, semantic_entities::union_*> unions;
	std::map<const semantic_entities::member_union*, semantic_entities::member_union*> member_unions;
	std::map<const semantic_entities::anonymous_union*, semantic_entities::anonymous_union*> anonymous_unions;
	std::map<const semantic_entities::anonymous_member_union*, semantic_entities::anonymous_member_union*> anonymous_member_unions;
	std::map<const semantic_entities::enum_*, semantic_entities::enum_*> enums;
	std::map<const semantic_entities::member_enum*, semantic_entities::member_enum*> member_enums;
	std::map<const semantic_entities::typedef_*, semantic_entities::typedef_*> typedefs;
	std::map<const semantic_entities::member_typedef*, semantic_entities::member_typedef*> member_typedefs;
	std::map<const semantic_entities::constructor*, semantic_entities::constructor*> constructors;
	std::map<const semantic_entities::destructor*, semantic_entities::destructor*> destructors;
	std::map<const semantic_entities::operator_member_function*, semantic_entities::operator_member_function*> operator_member_functions;
	std::map<const semantic_entities::conversion_function*, semantic_entities::conversion_function*> conversion_functions;
	std::map<const semantic_entities::simple_member_function*, semantic_entities::simple_member_function*> simple_member_functions;
	std::map<const semantic_entities::operator_function*, semantic_entities::operator_function*> operator_functions;
	std::map<const semantic_entities::simple_function*, semantic_entities::simple_function*> simple_functions;
	std::map<const semantic_entities::variable*, semantic_entities::variable*> variables;
	std::map<const semantic_entities::member_variable*, semantic_entities::member_variable*> member_variables;
	std::map<const semantic_entities::bit_field*, semantic_entities::bit_field*> bit_fields;



	template<class Entity>
	std::vector<old_and_new_entity_pair<Entity>>&
	get_pairs_of_type();

	template<class Entity>
	const std::vector<old_and_new_entity_pair<Entity>>&
	get_pairs_of_type() const;

	std::vector<old_and_new_entity_pair<semantic_entities::class_>> class_pairs;
	std::vector<old_and_new_entity_pair<semantic_entities::member_class>> member_class_pairs;
	std::vector<old_and_new_entity_pair<semantic_entities::union_>> union_pairs;
	std::vector<old_and_new_entity_pair<semantic_entities::member_union>> member_union_pairs;
	std::vector<old_and_new_entity_pair<semantic_entities::anonymous_union>> anonymous_union_pairs;
	std::vector<old_and_new_entity_pair<semantic_entities::anonymous_member_union>> anonymous_member_union_pairs;
};

}}}} //namespace scalpel::cpp::linkage::detail

#endif

