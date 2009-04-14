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

#include "parse_tree_to_syntax_tree/generic_convert_functions.hpp"
#include "parse_tree_to_syntax_tree/basic_functions.hpp"

namespace socoa { namespace cpp
{

using namespace socoa::cpp::syntax_tree;
using namespace socoa::cpp::parse_tree_to_syntax_tree;

syntax_tree_t
convert_parse_tree_to_syntax_tree(const tree_node_t& node)
{
	const tree_node_t& child_node = get_only_child_node(node);
    assert(child_node.value.id() == id_t::TRANSLATION_UNIT);

	tree_node_iterator_t grandchild_node = find_node<id_t::DECLARATION_SEQ>(child_node);
    if(grandchild_node != node.children.end()) //check whether the tree is not empty
	{
		return convert_nodes
		<
			declaration_seq,
			declaration,
			id_t::DECLARATION
		>
		(
			*grandchild_node
		);
	}
	else
	{
		return syntax_tree_t();
	}
}

}} //namespace socoa::cpp

