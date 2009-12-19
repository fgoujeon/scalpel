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

#ifndef SCALPEL_CPP_SYNTAX_NODES_TYPEOF_EXPRESSION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_TYPEOF_EXPRESSION_HPP

#include "expression.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
typeof_keyword
	= str_p("__typeof__")
	| "__typeof"
	| "typeof"
;
*/
typedef
	alternative_node
	<
		predefined_text_node<str::__typeof___>,
		predefined_text_node<str::__typeof_>,
		predefined_text_node<str::typeof_>
	>
	typeof_keyword
;

/**
typeof_expression
	= typeof_keyword >> !s >> '(' >> !s >> expression >> !s >> ')'
;
*/
typedef
	sequence_node
	<
		typeof_keyword,
		optional_node<space>,
		predefined_text_node<str::opening_round_bracket>,
		optional_node<space>,
		expression,
		optional_node<space>,
		predefined_text_node<str::closing_round_bracket>
	>
	typeof_expression
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif
