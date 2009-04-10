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

#ifndef SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_GENERIC_CONVERT_FUNCTIONS_HPP
#define SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_GENERIC_CONVERT_FUNCTIONS_HPP

#include <boost/optional.hpp>
#include "typedefs.hpp"
#include "node_converter.hpp"
#include "node_finder_and_converter.hpp"

namespace socoa { namespace cpp { namespace parse_tree_to_syntax_tree
{

/**
Converts a sequence of nodes.
*/
template<class ContainerT, class SyntaxNodeT, int... Ids>
ContainerT
convert_nodes(const tree_node_t& parent_node)
{
	ContainerT c;
    for(tree_node_iterator_t i = parent_node.children.begin(); i != parent_node.children.end(); ++i) //for each child node
	{
		const tree_node_t& child_node = *i;

		if(check_id<Ids...>(child_node))
			c.push_back(convert_node<SyntaxNodeT, Ids...>(child_node));
	}
	return c;
}

}}} //namespace socoa::cpp::parse_tree_to_syntax_tree

#endif
