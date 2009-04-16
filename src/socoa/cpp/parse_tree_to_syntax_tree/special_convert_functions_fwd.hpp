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

#ifndef SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_SPECIAL_CONVERT_FUNCTIONS_FWD_HPP
#define SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_SPECIAL_CONVERT_FUNCTIONS_FWD_HPP

#include <string>
#include <vector>
#include "../../util/sequence.hpp"
#include "../../util/string_enumeration.hpp"
#include "typedefs.hpp"
#include "convert_function_callers.hpp"

namespace socoa { namespace cpp { namespace parse_tree_to_syntax_tree
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

}}} //namespace socoa::cpp::parse_tree_to_syntax_tree

#endif
