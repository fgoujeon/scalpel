/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_NODE_CONVERTER_HPP
#define SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_NODE_CONVERTER_HPP

#include <string>
#include <iostream>
#include <boost/utility/enable_if.hpp>
#include "../../../syntax_tree.hpp"
#include "../../../syntax_nodes/util/node_type_traits.hpp"
#include "../grammar.hpp"
#include "sequence_node_converter_fwd.hpp"
#include "alternative_node_converter_fwd.hpp"
#include "other_node_converter.hpp"
#include "special_conversion_functions_fwd.hpp"

namespace scalpel { namespace cpp { namespace detail { namespace syntax_analysis { namespace parse_tree_to_syntax_tree
{

template<class T, class U>
struct is_same_type
{
	static const bool value = false;
};

template<class T>
struct is_same_type<T, T>
{
	static const bool value = true;
};



//overload for sequence nodes
template<class SyntaxNodeT>
inline
SyntaxNodeT
convert_node(const tree_node_t& node, typename SyntaxNodeT::tail_sequence_node_t* = 0)
{
	return convert_sequence_node<SyntaxNodeT>(node);
}

//overload for alternative nodes
template<class SyntaxNodeT>
inline
SyntaxNodeT
convert_node(const tree_node_t& node, typename SyntaxNodeT::tail_alternative_node_t* = 0)
{
	return convert_alternative_node<SyntaxNodeT>(node);
}

//overload for list nodes
template<class SyntaxNodeT>
inline
SyntaxNodeT
convert_node(const tree_node_t& node, typename boost::enable_if<syntax_nodes::util::is_list_node<SyntaxNodeT>>::type* = 0)
{
	return convert_list_node<SyntaxNodeT>(node);
}

//overload for optional nodes
template<class SyntaxNodeT>
inline
SyntaxNodeT
convert_node(const tree_node_t& node, typename boost::enable_if<syntax_nodes::util::is_optional_node<SyntaxNodeT>>::type* = 0)
{
	return convert_optional_node<SyntaxNodeT>(node);
}

//overload for predefined_text nodes
template<class SyntaxNodeT>
inline
SyntaxNodeT
convert_node(const tree_node_t& node, typename boost::enable_if<syntax_nodes::util::is_predefined_text_node<SyntaxNodeT>>::type* = 0)
{
	return convert_predefined_text_node<SyntaxNodeT>(node);
}

//overloads for other nodes

#define SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_CONVERT_NODE(node_type)	\
template<class SyntaxNodeT>																		\
inline																							\
syntax_nodes::node_type																			\
convert_node																					\
(																								\
	const tree_node_t& node,																	\
	typename boost::enable_if<is_same_type<SyntaxNodeT, syntax_nodes::node_type>>::type* = 0,	\
	typename boost::disable_if<syntax_nodes::util::is_sequence_node<SyntaxNodeT>>::type* = 0,		 	\
	typename boost::disable_if<syntax_nodes::util::is_alternative_node<SyntaxNodeT>>::type* = 0,	 	\
	typename boost::disable_if<syntax_nodes::util::is_list_node<SyntaxNodeT>>::type* = 0,			 	\
	typename boost::disable_if<syntax_nodes::util::is_optional_node<SyntaxNodeT>>::type* = 0,		 	\
	typename boost::disable_if<syntax_nodes::util::is_predefined_text_node<SyntaxNodeT>>::type* = 0	\
)																								\
{																								\
	return convert_##node_type(node);															\
}

SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_CONVERT_NODE(character_literal)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_CONVERT_NODE(direct_abstract_declarator)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_CONVERT_NODE(floating_literal)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_CONVERT_NODE(identifier)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_CONVERT_NODE(integer_literal)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_CONVERT_NODE(space)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_CONVERT_NODE(string_literal)

#undef SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_CONVERT_NODE

}}}}} //namespace scalpel::cpp::detail::syntax_analysis::parse_tree_to_syntax_tree

#endif
