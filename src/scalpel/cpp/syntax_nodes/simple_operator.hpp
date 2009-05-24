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

#ifndef SCALPEL_CPP_SYNTAX_NODES_SIMPLE_OPERATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_SIMPLE_OPERATOR_HPP

#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef
	alternative_node
	<
		simple_text_node<str::new_>,
		simple_text_node<str::delete_>,
		simple_text_node<str::double_right_angle_bracket_equal>,
		simple_text_node<str::double_left_angle_bracket_equal>,
		simple_text_node<str::arrow_asterisk>,
		simple_text_node<str::plus_equal>,
		simple_text_node<str::minus_equal>,
		simple_text_node<str::asterisk_equal>,
		simple_text_node<str::slash_equal>,
		simple_text_node<str::percent_equal>,
		simple_text_node<str::circumflex_equal>,
		simple_text_node<str::ampersand_equal>,
		simple_text_node<str::pipe_equal>,
		simple_text_node<str::double_left_angle_bracket>,
		simple_text_node<str::double_right_angle_bracket>,
		simple_text_node<str::double_equal>,
		simple_text_node<str::exclamation_equal>,
		simple_text_node<str::left_angle_bracket_equal>,
		simple_text_node<str::right_angle_bracket_equal>,
		simple_text_node<str::double_ampersand>,
		simple_text_node<str::double_pipe>,
		simple_text_node<str::double_plus>,
		simple_text_node<str::double_minus>,
		simple_text_node<str::arrow>,
		simple_text_node<str::round_brackets>,
		simple_text_node<str::square_brackets>,
		simple_text_node<str::comma>,
		simple_text_node<str::plus>,
		simple_text_node<str::minus>,
		simple_text_node<str::asterisk>,
		simple_text_node<str::slash>,
		simple_text_node<str::percent>,
		simple_text_node<str::circumflex>,
		simple_text_node<str::ampersand>,
		simple_text_node<str::pipe>,
		simple_text_node<str::tilde>,
		simple_text_node<str::exclamation>,
		simple_text_node<str::equal>,
		simple_text_node<str::left_angle_bracket>,
		simple_text_node<str::right_angle_bracket>
	>
	simple_operator
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif
