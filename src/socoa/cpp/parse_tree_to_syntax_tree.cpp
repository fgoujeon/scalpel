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

#include "parse_tree_to_syntax_tree.hpp"

#include "parse_tree_to_syntax_tree/generic_node_converters.hpp"
#include "parse_tree_to_syntax_tree/node_finder.hpp"
#include "parse_tree_to_syntax_tree/basic_functions.hpp"

namespace socoa { namespace cpp
{

using namespace socoa::cpp::syntax_nodes;
using namespace socoa::cpp::parse_tree_to_syntax_tree;

syntax_tree
convert_parse_tree_to_syntax_tree(const tree_node_t& node)
{
	const tree_node_t& child_node = get_only_child_node(node);
	return parse_tree_to_syntax_tree::convert_translation_unit(child_node);
}

}} //namespace socoa::cpp

