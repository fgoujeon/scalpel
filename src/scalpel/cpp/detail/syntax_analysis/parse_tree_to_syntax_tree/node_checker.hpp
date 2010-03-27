/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#ifndef SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_NODE_CHECKER_HPP
#define SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_NODE_CHECKER_HPP

#include "syntax_node_type_to_parser_id_map.hpp"
#include "basic_functions.hpp"
#include <scalpel/cpp/syntax_nodes/predefined_text_node.hpp>
#include <string>

namespace scalpel { namespace cpp { namespace detail { namespace syntax_analysis { namespace parse_tree_to_syntax_tree
{

//check from id by default
template<class NodeT>
struct node_checker
{
	static
	bool
	check(const tree_node_t& node)
	{
		return syntax_node_type_to_parser_id_map<NodeT>::parser_id() == node.value.id();
	}
};

//check from value for simple text nodes (since they don't have an id)
template<const std::string& Text>
struct node_checker<syntax_nodes::predefined_text_node<Text>>
{
	static
	bool
	check(const tree_node_t& node)
	{
		return get_value(node) == Text;
	}
};

/**
 * Checks whether the type of the parse tree node is the one that is expected
 * to be converted into the given syntax tree node type.
 */
template<class SyntaxNodeT>
bool
check_node(const tree_node_t& node)
{
	return node_checker<SyntaxNodeT>::check(node);
}

}}}}} //namespace scalpel::cpp::detail::syntax_analysis::parse_tree_to_syntax_tree

#endif
