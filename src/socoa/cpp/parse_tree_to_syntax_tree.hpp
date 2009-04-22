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

#ifndef SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_HPP
#define SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_HPP

#include "syntax_tree.hpp"
#include "parse_tree_to_syntax_tree/typedefs.hpp"

namespace socoa { namespace cpp
{

syntax_tree
convert_parse_tree_to_syntax_tree(const parse_tree_to_syntax_tree::tree_node_t& node);

}} //namespace socoa::cpp

#endif
