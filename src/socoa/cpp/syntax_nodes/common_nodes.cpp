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

#include "common_nodes.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

//symbols
const leaf_node ampersand("&");
const leaf_node arrow_and_asterisk("->*");
const leaf_node asterisk("*");
const leaf_node capital_l("L");
const leaf_node circumflex("^");
const leaf_node closing_angle_bracket(">");
const leaf_node closing_brace("}");
const leaf_node closing_bracket(")");
const leaf_node closing_square_bracket("]");
const leaf_node colon(":");
const leaf_node comma(",");
const leaf_node dot(".");
const leaf_node dot_and_asterisk(".*");
const leaf_node double_ampersand("&&");
const leaf_node double_colon("::");
const leaf_node double_equal("==");
const leaf_node double_left_angle_bracket("<<");
const leaf_node double_pipe("||");
const leaf_node double_quote("\"");
const leaf_node double_right_angle_bracket(">>");
const leaf_node empty("");
const leaf_node equal("=");
const leaf_node inequal("!=");
const leaf_node left_angle_bracket("<");
const leaf_node left_angle_bracket_and_equal("<=");
const leaf_node minus("-");
const leaf_node opening_angle_bracket("<");
const leaf_node opening_brace("{");
const leaf_node opening_bracket("(");
const leaf_node opening_square_bracket("[");
const leaf_node percent("%");
const leaf_node pipe("|");
const leaf_node plus("+");
const leaf_node right_angle_bracket(">");
const leaf_node right_angle_bracket_and_equal(">=");
const leaf_node semicolon(";");
const leaf_node single_quote("'");
const leaf_node slash("/");
const leaf_node tilde("~");

//keywords
const leaf_node break_keyword("break");
const leaf_node case_keyword("case");
const leaf_node catch_keyword("catch");
const leaf_node continue_keyword("continue");
const leaf_node default_keyword("default");
const leaf_node else_keyword("else");
const leaf_node for_keyword("for");
const leaf_node goto_keyword("goto");
const leaf_node if_keyword("if");
const leaf_node namespace_keyword("namespace");
const leaf_node operator_keyword("operator");
const leaf_node return_keyword("return");
const leaf_node switch_keyword("switch");
const leaf_node template_keyword("template");
const leaf_node throw_keyword("throw");
const leaf_node try_keyword("try");
const leaf_node using_keyword("using");
const leaf_node virtual_keyword("virtual");

}}} //namespace socoa::cpp::syntax_nodes

