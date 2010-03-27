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

#ifndef SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_NODE_CONVERTER_HPP
#define SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_NODE_CONVERTER_HPP

#include "sequence_node_converter_fwd.hpp"
#include "alternative_node_converter_fwd.hpp"
#include "leaf_node_converter.hpp"
#include "special_conversion_functions_fwd.hpp"
#include "syntax_node_type_to_parser_id_map.hpp"
#include "basic_functions.hpp"
#include "../grammar.hpp"
#include "../../../syntax_tree.hpp"
#include "../../../syntax_nodes/utility/type_traits.hpp"
#include <boost/utility/enable_if.hpp>
#include <string>
#include <iostream>

namespace scalpel { namespace cpp { namespace detail { namespace syntax_analysis { namespace parse_tree_to_syntax_tree
{

template<class SyntaxNodeT>
void
assert_node_id(const tree_node_t& node)
{
	boost::spirit::parser_id checked_id = node.value.id();
	boost::spirit::parser_id correct_id = syntax_node_type_to_parser_id_map<SyntaxNodeT>::parser_id();

	if(checked_id != correct_id)
	{
		std::cout << "Error: parser id is " << checked_id << ", but " << correct_id << " was expected.\n";
		assert(false);
	}
}



//overload for sequence nodes
template<class SyntaxNodeT>
inline
SyntaxNodeT
convert_node
(
	const tree_node_t& node,
	typename SyntaxNodeT::tail_sequence_node_t* = 0
)
{
#ifndef NDEBUG
	assert_node_id<SyntaxNodeT>(node);
#endif
	return convert_sequence_node<SyntaxNodeT>(node);
}

//overload for alternative nodes
template<class SyntaxNodeT>
inline
SyntaxNodeT
convert_node
(
	const tree_node_t& node,
	typename SyntaxNodeT::tail_alternative_node_t* = 0
)
{
#ifndef NDEBUG
	assert_node_id<SyntaxNodeT>(node);
#endif
	return convert_alternative_node<SyntaxNodeT>(node);
}

//overload for list nodes
template<class SyntaxNodeT>
inline
SyntaxNodeT
convert_node
(
	const tree_node_t& node,
	typename boost::enable_if<syntax_nodes::utility::is_list_node<SyntaxNodeT>>::type* = 0
)
{
#ifndef NDEBUG
	assert_node_id<SyntaxNodeT>(node);
#endif
	return convert_list_node<SyntaxNodeT>(node);
}

//overload for optional nodes
template<class SyntaxNodeT>
inline
SyntaxNodeT
convert_node
(
	const tree_node_t& node,
	typename boost::enable_if<syntax_nodes::utility::is_optional_node<SyntaxNodeT>>::type* = 0
)
{
#ifndef NDEBUG
	assert_node_id<SyntaxNodeT>(node);
#endif
	return convert_optional_node<SyntaxNodeT>(node);
}

//overload for predefined_text nodes
template<class SyntaxNodeT>
inline
SyntaxNodeT
convert_node
(
	const tree_node_t& node,
	typename boost::enable_if<syntax_nodes::utility::is_predefined_text_node<SyntaxNodeT>>::type* = 0
)
{
	return convert_predefined_text_node<SyntaxNodeT>(node);
}

//overload for leaf nodes
template<class SyntaxNodeT>
inline
SyntaxNodeT
convert_node
(
	const tree_node_t& node,
	typename boost::enable_if<syntax_nodes::utility::is_leaf_node<SyntaxNodeT>>::type* = 0
)
{
	return convert_leaf_node<SyntaxNodeT>(node);
}

}}}}} //namespace scalpel::cpp::detail::syntax_analysis::parse_tree_to_syntax_tree

#endif
