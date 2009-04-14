/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_NODE_FINDER_HPP
#define SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_NODE_FINDER_HPP

#include "typedefs.hpp"
#include "basic_functions.hpp"

namespace socoa { namespace cpp { namespace parse_tree_to_syntax_tree
{

template<const id_t... Ids>
struct node_finder;

template<>
struct node_finder<>
{
	static
	tree_node_iterator_t
	find(const tree_node_t& parent_node)
	{
		return parent_node.children.end();
	}
};

template<const id_t Id, const grammar::parser_id... Ids>
struct node_finder<Id, Ids...>
{
	static
	tree_node_iterator_t
	find(const tree_node_t& parent_node)
	{
		tree_node_iterator_t found_node = find_child_node(parent_node, Id);
		if(found_node != parent_node.children.end())
			return found_node;
		else
			return node_finder<Ids...>::find(parent_node);
	}
};

/**
Convenient free function to be used in place of node_finder class.
*/
template<const id_t... Ids>
inline
tree_node_iterator_t
find_node(const tree_node_t& parent_node)
{
	return node_finder<Ids...>::find(parent_node);
}

}}} //namespace socoa::cpp::parse_tree_to_syntax_tree

#endif
