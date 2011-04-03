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

#ifndef SCALPEL_CPP_SYNTAX_NODES_ASM_DEFINITION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_ASM_DEFINITION_HPP

#include "string_literal.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
asm_definition
	= str_p("asm") >> !s >> '(' >> !s >> string_literal >> !s >> ')' >> !s >> ch_p(';')
;
*/
typedef
	sequence_node
	<
		predefined_text_node<str::asm_>,
		predefined_text_node<str::opening_round_bracket>,
		string_literal,
		predefined_text_node<str::closing_round_bracket>,
		predefined_text_node<str::semicolon>
	>
	asm_definition
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif
