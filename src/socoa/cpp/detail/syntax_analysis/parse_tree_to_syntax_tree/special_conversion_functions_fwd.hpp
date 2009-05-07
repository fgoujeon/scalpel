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

#ifndef SOCOA_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_SPECIAL_CONVERT_FUNCTIONS_FWD_HPP
#define SOCOA_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_SPECIAL_CONVERT_FUNCTIONS_FWD_HPP

#include <string>
#include <vector>
#include "typedefs.hpp"
#include "generic_node_converters.hpp"

namespace socoa { namespace cpp { namespace detail { namespace syntax_analysis { namespace parse_tree_to_syntax_tree
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
convert_sequence(const tree_node_t& node);

template<class SyntaxNodeT, int... Ids>
inline
SyntaxNodeT
convert_alternative(const tree_node_t& node);

template<class T>
boost::optional<T>
convert_optional(const tree_node_t& parent_node, const tree_node_iterator_t& it);

template<const std::string&& Text>
syntax_nodes::simple_text_node<Text>
convert_simple_text(const tree_node_t&);

}}}}} //namespace socoa::cpp::detail::syntax_analysis::parse_tree_to_syntax_tree

#endif
