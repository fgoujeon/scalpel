/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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

#ifndef CPP2XML_SYNTAX_TREE_HPP
#define CPP2XML_SYNTAX_TREE_HPP

#include "detail/json_writer.hpp"
#include <scalpel/cpp/syntax_tree.hpp>
#include <scalpel/cpp/syntax_nodes/utility/type_traits.hpp>
#include <iostream>

namespace cpp2json
{

inline
void
print_syntax_tree(const scalpel::cpp::syntax_tree& tree);

//overload for sequence nodes
template<class SyntaxNode>
void
print
(
	const SyntaxNode& node,
	detail::json_writer& writer,
	const bool print_node_type = true,
	typename boost::enable_if<syntax_nodes::utility::is_sequence_node<SyntaxNode>>::type* = 0
);

//overload for alternative nodes
template<class SyntaxNode>
void
print
(
	const SyntaxNode& node,
	detail::json_writer& writer,
	const bool print_node_type = true,
	typename boost::enable_if<syntax_nodes::utility::is_alternative_node<SyntaxNode>>::type* = 0
);

//overload for list nodes
template<class SyntaxNode>
void
print
(
	const SyntaxNode& node,
	detail::json_writer& writer,
	typename boost::enable_if<syntax_nodes::utility::is_list_node<SyntaxNode>>::type* = 0
);

//overload for optional nodes
template<class SyntaxNode>
void
print
(
	const SyntaxNode& node,
	detail::json_writer& writer,
	typename boost::enable_if<syntax_nodes::utility::is_optional_node<SyntaxNode>>::type* = 0
);

//overload for predefined_text nodes
template<class SyntaxNode>
void
print
(
	const SyntaxNode& node,
	detail::json_writer& writer,
	typename boost::enable_if<syntax_nodes::utility::is_predefined_text_node<SyntaxNode>>::type* = 0
);

//overload for leaf nodes
template<class SyntaxNode>
void
print
(
	const SyntaxNode& node,
	detail::json_writer& writer,
	typename boost::enable_if<syntax_nodes::utility::is_leaf_node<SyntaxNode>>::type* = 0
);

} //namespace cpp2json

#include "syntax_tree.ipp"

#endif

