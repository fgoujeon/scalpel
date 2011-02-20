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

#ifndef SCALPEL_CPP_LINKING_DETAIL_LINKING_TREE_CLASS_HPP
#define SCALPEL_CPP_LINKING_DETAIL_LINKING_TREE_CLASS_HPP

#include "entity_list.hpp"
#include <scalpel/cpp/semantic_graph.hpp>
#include <vector>

namespace scalpel { namespace cpp { namespace linking { namespace detail { namespace linking_tree
{

struct class_
{
	std::map<std::string, class_> classes;
	entity_list<semantic_entities::enum_> enums;
	entity_list<semantic_entities::typedef_> typedefs;
	entity_list<semantic_entities::constructor> constructors;
	entity_list<semantic_entities::destructor> destructors;
	entity_list<semantic_entities::operator_member_function> operator_member_functions;
	entity_list<semantic_entities::conversion_function> conversion_functions;
	entity_list<semantic_entities::simple_member_function> simple_member_functions;
	entity_list<semantic_entities::variable> variables;
};

template<class Entity>
entity_list<Entity>&
get_entities(class_& n);

template<class Entity>
const entity_list<Entity>&
get_entities(const class_& n);

}}}}} //namespace scalpel::cpp::linking::detail::linking_tree

#endif

