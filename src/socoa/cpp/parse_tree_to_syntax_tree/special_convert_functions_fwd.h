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

#ifndef SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_SPECIAL_CONVERT_FUNCTIONS_FWD_H
#define SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_SPECIAL_CONVERT_FUNCTIONS_FWD_H

#include <string>
#include <vector>
#include "../../util/sequence.h"
#include "../../util/string_enumeration.h"
#include "typedefs.h"
#include "convert_function_callers.h"

namespace socoa { namespace cpp { namespace parse_tree_to_syntax_tree
{

template
<
	class T,
	const std::string& Separator// = util::extern_strings::space
>
util::sequence<T, Separator>
convert_sequence(const tree_node_t& node);

template<class T>
T
convert_string_enumeration(const tree_node_t& node);

/**
Converts each child node of the given parent node. All the nodes must
be of the same type.
@tparam T the type representing the syntax of the nodes to be converted
@param parent_node the parent node where to find the nodes to be
	   converted
@param separator value of the nodes to be ignored (useful for comma
	   separated lists)
@return a vector of pointers to objects representing the syntax of each
		converted node
*/
template <class T>
std::vector<T>
convert_separated_nodes
(
	const tree_node_t& parent_node,
	const std::string& separator
);

}}} //namespace socoa::cpp::parse_tree_to_syntax_tree

#endif
