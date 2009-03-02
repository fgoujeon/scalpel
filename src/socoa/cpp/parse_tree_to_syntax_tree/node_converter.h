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

#ifndef SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_NODE_CONVERTER_H
#define SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_NODE_CONVERTER_H

#include "typedefs.h"
#include "basic_functions.h"
#include "convert_function_callers.h"

namespace socoa { namespace cpp { namespace parse_tree_to_syntax_tree
{

/**
Convert the parse_tree node given to the convert() static function to the
corresponding syntax_tree node.
\tparam SyntaxNodeT type of the syntax_node (must be a boost::variant<...>)
\tparam Ids list of the potential values of the given node's parser_id
*/
template<class SyntaxNodeT, int... Ids>
struct node_converter;

template<class SyntaxNodeT>
struct node_converter<SyntaxNodeT>
{
	static
	SyntaxNodeT
	convert(const tree_node_t&)
	{
		assert(false);
	}
};

//If the node is optional, return an empty node instead of
//throwing an error.
template<class SyntaxNodeT>
struct node_converter<boost::optional<SyntaxNodeT>>
{
	static
	boost::optional<SyntaxNodeT>
	convert(const tree_node_t&)
	{
		return boost::optional<SyntaxNodeT>();
	}
};

template<class SyntaxNodeT, int Id, int... Ids>
struct node_converter<SyntaxNodeT, Id, Ids...>
{
	static
	SyntaxNodeT
	convert(const tree_node_t& node)
	{
		const int node_id = get_id(node);
		if(node_id == Id)
		{
			return SyntaxNodeT(convert_function_caller_from_id<SyntaxNodeT, Id>::convert(node));
		}
		else
		{
			return node_converter<SyntaxNodeT, Ids...>::convert(node);
		}
	}
};

/**
 * Convenient free function to be used in place of node_converter class.
 */
template<class SyntaxNodeT, int... Ids>
inline
SyntaxNodeT
convert_node(const tree_node_t& node)
{
	return node_converter<SyntaxNodeT, Ids...>::convert(node);
}

}}} //namespace socoa::cpp::parse_tree_to_syntax_tree

#endif
