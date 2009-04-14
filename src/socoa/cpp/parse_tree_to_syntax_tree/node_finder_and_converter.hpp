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

#ifndef SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_NODE_FINDER_AND_CONVERTER_HPP
#define SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_NODE_FINDER_AND_CONVERTER_HPP

#include <boost/optional.hpp>
#include "../grammar.hpp"
#include "typedefs.hpp"
#include "basic_functions.hpp"
#include "node_converter.hpp"
#include "node_finder.hpp"

namespace socoa { namespace cpp { namespace parse_tree_to_syntax_tree
{

/**
Finds a node corresponding to the given parser id among the child nodes of the
given parent node and converts it.
*/
template<class SyntaxNodeT, grammar::parser_id... Ids>
struct node_finder_and_converter
{
	static
	SyntaxNodeT
	convert(const tree_node_t& parent_node)
	{
		tree_node_iterator_t child_node = find_node<Ids...>(parent_node);
		assert(child_node != parent_node.children.end());
		return node_converter<SyntaxNodeT, Ids...>::convert
		(
			*child_node
		);
	}
};

template<class SyntaxNodeT, grammar::parser_id... Ids>
struct node_finder_and_converter<boost::optional<SyntaxNodeT>, Ids...>
{
	static
	boost::optional<SyntaxNodeT>
	convert(const tree_node_t& parent_node)
	{
		tree_node_iterator_t child_node = find_node<Ids...>(parent_node);
		if(child_node != parent_node.children.end())
			return boost::optional<SyntaxNodeT>
			(
				node_converter<SyntaxNodeT, Ids...>::convert
				(
					*child_node
				)
			);
		else
			return boost::optional<SyntaxNodeT>();
	}
};

/**
 * Convenient free function to be used in place of node_finder_and_converter
 * class.
 */
template<class SyntaxNodeT, grammar::parser_id... Ids>
SyntaxNodeT
find_and_convert_node(const tree_node_t& parent_node)
{
	return node_finder_and_converter<SyntaxNodeT, Ids...>::convert(parent_node);
}

}}} //namespace socoa::cpp::parse_tree_to_syntax_tree

#endif
