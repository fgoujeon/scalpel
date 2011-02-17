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

#ifndef SCALPEL_CPP_LINKING_DETAIL_ENTITY_TREE_HPP
#define SCALPEL_CPP_LINKING_DETAIL_ENTITY_TREE_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <vector>

namespace scalpel { namespace cpp { namespace linking { namespace detail
{

template<class Entity>
struct entity_list
{
	std::map<std::string, std::vector<const Entity*>> list;
};

struct entity_tree
{
	enum class tree_type
	{
		NAMESPACE,
		CLASS
	};

	explicit
	entity_tree(tree_type t);

	template<class Entity>
	entity_list<Entity>&
	entities();

	template<class Entity>
	const entity_list<Entity>&
	entities() const;

	tree_type type;
	std::map<std::string, entity_tree> subtrees;
	entity_list<semantic_entities::enum_> enums;
	entity_list<semantic_entities::typedef_> typedefs;
	entity_list<semantic_entities::constructor> constructors;
	entity_list<semantic_entities::destructor> destructors;
	entity_list<semantic_entities::operator_member_function> operator_member_functions;
	entity_list<semantic_entities::conversion_function> conversion_functions;
	entity_list<semantic_entities::simple_member_function> simple_member_functions;
	entity_list<semantic_entities::operator_function> operator_functions;
	entity_list<semantic_entities::simple_function> simple_functions;
	entity_list<semantic_entities::variable> variables;
};

}}}} //namespace scalpel::cpp::linking::detail

#endif

