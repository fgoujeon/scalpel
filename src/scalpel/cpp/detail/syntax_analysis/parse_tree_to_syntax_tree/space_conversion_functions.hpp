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

#ifndef SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_SPACE_CONVERT_FUNCTIONS_HPP
#define SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_SPACE_CONVERT_FUNCTIONS_HPP

#include "../../../syntax_nodes/optional_node.hpp"
#include "../../../syntax_nodes/space.hpp"
#include "typedefs.hpp"

namespace scalpel { namespace cpp { namespace detail { namespace syntax_analysis { namespace parse_tree_to_syntax_tree
{

/**
 * Check whether the previous node is a space node, and if so, convert it.
 */
syntax_nodes::optional_node<syntax_nodes::space>
convert_previous_space(const tree_node_t& parent_node, tree_node_iterator_t i);

/**
 * Check whether the next node is a space node, and if so, convert it.
 */
syntax_nodes::optional_node<syntax_nodes::space>
convert_next_space(const tree_node_t& parent_node, tree_node_iterator_t i);

}}}}} //namespace scalpel::cpp::detail::syntax_analysis::parse_tree_to_syntax_tree

#endif
