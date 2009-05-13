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

#ifndef SCALPEL_CPP_SYNTAX_NODES_COMMON_NODES_HPP
#define SCALPEL_CPP_SYNTAX_NODES_COMMON_NODES_HPP

#include <string>
#include "leaf_node.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes { namespace global_nodes
{

//symbols
extern const leaf_node ampersand;
extern const leaf_node arrow;
extern const leaf_node arrow_and_asterisk;
extern const leaf_node asterisk;
extern const leaf_node capital_l;
extern const leaf_node circumflex;
extern const leaf_node closing_angle_bracket;
extern const leaf_node closing_brace;
extern const leaf_node closing_bracket;
extern const leaf_node closing_square_bracket;
extern const leaf_node colon;
extern const leaf_node comma;
extern const leaf_node dot;
extern const leaf_node dot_and_asterisk;
extern const leaf_node double_ampersand;
extern const leaf_node double_colon;
extern const leaf_node double_equal;
extern const leaf_node double_left_angle_bracket;
extern const leaf_node double_pipe;
extern const leaf_node double_quote;
extern const leaf_node double_right_angle_bracket;
extern const leaf_node empty;
extern const leaf_node equal;
extern const leaf_node inequal;
extern const leaf_node left_angle_bracket;
extern const leaf_node left_angle_bracket_and_equal;
extern const leaf_node minus;
extern const leaf_node opening_angle_bracket;
extern const leaf_node opening_brace;
extern const leaf_node opening_bracket;
extern const leaf_node opening_square_bracket;
extern const leaf_node percent;
extern const leaf_node pipe;
extern const leaf_node plus;
extern const leaf_node right_angle_bracket;
extern const leaf_node right_angle_bracket_and_equal;
extern const leaf_node semicolon;
extern const leaf_node single_quote;
extern const leaf_node slash;
extern const leaf_node tilde;

//keywords
extern const leaf_node break_keyword;
extern const leaf_node case_keyword;
extern const leaf_node catch_keyword;
extern const leaf_node const_cast_keyword;
extern const leaf_node continue_keyword;
extern const leaf_node default_keyword;
extern const leaf_node delete_keyword;
extern const leaf_node do_keyword;
extern const leaf_node else_keyword;
extern const leaf_node false_keyword;
extern const leaf_node for_keyword;
extern const leaf_node goto_keyword;
extern const leaf_node if_keyword;
extern const leaf_node namespace_keyword;
extern const leaf_node new_keyword;
extern const leaf_node operator_keyword;
extern const leaf_node return_keyword;
extern const leaf_node switch_keyword;
extern const leaf_node template_keyword;
extern const leaf_node throw_keyword;
extern const leaf_node true_keyword;
extern const leaf_node try_keyword;
extern const leaf_node using_keyword;
extern const leaf_node virtual_keyword;
extern const leaf_node while_keyword;

}}}} //namespace scalpel::cpp::syntax_nodes::global_nodes

#endif
