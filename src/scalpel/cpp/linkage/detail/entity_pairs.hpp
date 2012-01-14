/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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

#ifndef SCALPEL_CPP_LINKAGE_DETAIL_ENTITY_PAIRS_HPP
#define SCALPEL_CPP_LINKAGE_DETAIL_ENTITY_PAIRS_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <vector>

namespace scalpel { namespace cpp { namespace linkage { namespace detail
{

template<class Entity>
struct old_and_new_entity_pair
{
	const Entity* old_entity;
	Entity* new_entity;
};

struct entity_pairs
{
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
	std::vector<old_and_new_entity_pair<semantic_entities::variable>> variable_pairs;
};

}}}} //namespace scalpel::cpp::linkage::detail

#endif

