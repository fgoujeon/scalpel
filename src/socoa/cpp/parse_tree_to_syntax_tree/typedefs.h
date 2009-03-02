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

#ifndef SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_TYPEDEFS_H
#define SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_TYPEDEFS_H

#include <string>
#include <boost/spirit/tree/parse_tree.hpp>
#include "../grammar.h"

namespace socoa { namespace cpp { namespace parse_tree_to_syntax_tree
{

typedef char const* iterator_t;
typedef boost::spirit::tree_match<iterator_t> parse_tree_match_t;
typedef parse_tree_match_t::container_t tree_t;
typedef parse_tree_match_t::node_t tree_node_t;
typedef parse_tree_match_t::const_tree_iterator tree_node_iterator_t;
typedef tree_node_t::parse_node_t tree_node_value_t;
typedef tree_node_value_t::const_iterator_t tree_node_value_iterator_t;

typedef grammar::parser_id id_t;

}}} //namespace socoa::cpp::parse_tree_to_syntax_tree

#endif
