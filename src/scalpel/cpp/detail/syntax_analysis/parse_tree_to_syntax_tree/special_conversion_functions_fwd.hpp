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

#ifndef SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_SPECIAL_CONVERT_FUNCTIONS_FWD_HPP
#define SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_SPECIAL_CONVERT_FUNCTIONS_FWD_HPP

#include <string>
#include <vector>
#include <scalpel/cpp/syntax_tree.hpp>
#include "typedefs.hpp"

namespace scalpel { namespace cpp { namespace detail { namespace syntax_analysis { namespace parse_tree_to_syntax_tree
{

template<class T>
T
convert_string_enumeration(const tree_node_t& node);

/**
Converts each child node of the given parent node. All the nodes must
be of the same type.
@tparam ContainerT the type representing the syntax of the sequence node to be converted
@param node the parse node of the sequence node
@return the syntax node of the sequence
*/
template<class ContainerT>
ContainerT
convert_list_node(const tree_node_t& node);

template<class T>
syntax_nodes::optional_node<T>
convert_optional(const tree_node_t& parent_node, const tree_node_iterator_t& it);


template<class SyntaxNodeT>
typename syntax_nodes::round_bracketed_node<SyntaxNodeT>::type
convert_round_bracketed_node(const tree_node_t& node);

template<class SyntaxNodeT>
typename syntax_nodes::square_bracketed_node<SyntaxNodeT>::type
convert_square_bracketed_node(const tree_node_t& node);

template<class SyntaxNodeT>
typename syntax_nodes::angle_bracketed_node<SyntaxNodeT>::type
convert_angle_bracketed_node(const tree_node_t& node);

template<const syntax_nodes::leaf_node& OpeningBracketNode, class SyntaxNodeT, const syntax_nodes::leaf_node& ClosingBracketNode>
syntax_nodes::bracketed_node<OpeningBracketNode, SyntaxNodeT, ClosingBracketNode>
convert_bracketed_node(const tree_node_t& node);

template<class SyntaxNodeT>
typename syntax_nodes::round_bracketed_node<SyntaxNodeT>::type
convert_round_bracketed_node(tree_node_iterator_t it);

template<class SyntaxNodeT>
typename syntax_nodes::square_bracketed_node<SyntaxNodeT>::type
convert_square_bracketed_node(tree_node_iterator_t it);

template<class SyntaxNodeT>
typename syntax_nodes::angle_bracketed_node<SyntaxNodeT>::type
convert_angle_bracketed_node(tree_node_iterator_t it);

template<const syntax_nodes::leaf_node& OpeningBracketNode, class SyntaxNodeT, const syntax_nodes::leaf_node& ClosingBracketNode>
syntax_nodes::bracketed_node<OpeningBracketNode, SyntaxNodeT, ClosingBracketNode>
convert_bracketed_node(tree_node_iterator_t it);


template<const std::string&& Text>
syntax_nodes::simple_text_node<Text>
convert_simple_text(const tree_node_t&);

}}}}} //namespace scalpel::cpp::detail::syntax_analysis::parse_tree_to_syntax_tree

#endif
