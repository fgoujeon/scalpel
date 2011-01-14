/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

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

#ifndef SCALPEL_CPP_SYNTAX_ANALYSIS_DETAIL_PARSE_TREE_TO_SYNTAX_TREE_BASIC_FUNCTIONS_HPP
#define SCALPEL_CPP_SYNTAX_ANALYSIS_DETAIL_PARSE_TREE_TO_SYNTAX_TREE_BASIC_FUNCTIONS_HPP

#include "typedefs.hpp"
#include <string>

namespace scalpel { namespace cpp { namespace syntax_analysis { namespace detail { namespace parse_tree_to_syntax_tree
{

inline
const tree_node_t&
get_only_child_node(const tree_node_t& parent_node);

std::string
get_value(const tree_node_t& node);

std::string
get_only_child_value(const tree_node_t& node);



inline
const tree_node_t&
get_only_child_node(const tree_node_t& parent_node)
{
	assert(parent_node.children.size() == 1);
	return *parent_node.children.begin();
}

std::ostream&
operator<<(std::ostream& o, const boost::spirit::parser_id& id);

}}}}} //namespace scalpel::cpp::syntax_analysis::detail

#endif
