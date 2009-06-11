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

#ifndef SCALPEL_CPP_SYNTAX_NODES_TYPENAME_EXPRESSION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_TYPENAME_EXPRESSION_HPP

#include "common.hpp"
#include "nested_name_specifier.hpp"
#include "identifier.hpp"
#include "expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
typename_expression
	= str_p("typename") >> !s >> !(str_p("::") >> !s) >> nested_name_specifier >> !s >> identifier >> !s >> '(' >> !s >> !(expression >> !s) >> ')'
;
*/
typedef
	sequence_node
	<
		simple_text_node<str::typename_>,
		optional_node<space>,
		optional_node<simple_text_node<str::double_colon>>,
		optional_node<space>,
		nested_name_specifier,
		optional_node<space>,
		identifier,
		optional_node<space>,
		simple_text_node<str::opening_round_bracket>,
		optional_node<space>,
		optional_node<expression>,
		optional_node<space>,
		simple_text_node<str::closing_round_bracket>
	>
	typename_expression
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif
