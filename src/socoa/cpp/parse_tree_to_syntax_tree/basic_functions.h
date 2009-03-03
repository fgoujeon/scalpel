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

#ifndef SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_BASIC_FUNCTIONS_H
#define SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_BASIC_FUNCTIONS_H

#include <string>
#include "typedefs.h"

namespace socoa { namespace cpp { namespace parse_tree_to_syntax_tree
{

inline
const tree_node_t&
get_only_child_node(const tree_node_t& parent_node);

const tree_node_t*
find_child_node(const tree_node_t& parent_node, const id_t child_id);

bool
check_node_existence(const tree_node_t& parent_node, const std::string& value, unsigned int position);

bool
check_node_existence(const tree_node_t& parent_node, const std::string& value);

bool
check_node_existence(const tree_node_t& parent_node, const grammar::parser_id id, unsigned int position);

bool
check_node_existence(const tree_node_t& parent_node, const grammar::parser_id id);

std::string
get_value(const tree_node_t& node);

std::string
get_only_child_value(const tree_node_t& node);

std::string
strip_redundant_spaces(const std::string& str);

int
get_id(const tree_node_t& node);


inline
const tree_node_t&
get_only_child_node(const tree_node_t& parent_node)
{
	assert(parent_node.children.size() == 1);
	return *parent_node.children.begin();
}

}}} //namespace socoa::cpp

#endif