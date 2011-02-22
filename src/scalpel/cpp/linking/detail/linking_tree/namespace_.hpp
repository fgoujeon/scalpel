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

#ifndef SCALPEL_CPP_LINKING_DETAIL_LINKING_TREE_NAMESPACE_HPP
#define SCALPEL_CPP_LINKING_DETAIL_LINKING_TREE_NAMESPACE_HPP

#include "entity_list.hpp"
#include "class_.hpp"
#include <scalpel/cpp/semantic_graph.hpp>
#include <vector>

namespace scalpel { namespace cpp { namespace linking { namespace detail { namespace linking_tree
{

struct namespace_
{
	std::map<std::string, namespace_> namespaces;
	std::map<std::string, class_> classes;
	entity_list<semantic_entities::enum_> enums;
	entity_list<semantic_entities::typedef_> typedefs;
	entity_list<semantic_entities::operator_function> operator_functions;
	entity_list<semantic_entities::simple_function> simple_functions;
	entity_list<semantic_entities::variable> variables;
};

template<class Entity>
entity_list<Entity>&
get_entity_list(namespace_& n);

template<class Entity>
const entity_list<Entity>&
get_entity_list(const namespace_& n);

}}}}} //namespace scalpel::cpp::linking::detail::linking_tree

#endif
