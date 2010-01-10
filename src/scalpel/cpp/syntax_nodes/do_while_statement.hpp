/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#ifndef SCALPEL_CPP_SYNTAX_NODES_DO_WHILE_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_DO_WHILE_STATEMENT_HPP

#include "statement.hpp"
#include "expression.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
do_while_statement
	= str_p("do") >> !s >> statement >> !s >> "while" >> !s >> '(' >> !s >> expression >> !s >> ')' >> !s >> ch_p(';')
;
*/
typedef
	sequence_node
	<
		predefined_text_node<str::do_>,
		optional_node<space>,
		statement,
		optional_node<space>,
		predefined_text_node<str::while_>,
		optional_node<space>,
		predefined_text_node<str::opening_round_bracket>,
		optional_node<space>,
		expression,
		optional_node<space>,
		predefined_text_node<str::closing_round_bracket>,
		optional_node<space>,
		predefined_text_node<str::semicolon>
	>
	do_while_statement
;

inline
const statement&
get_statement(const do_while_statement& o)
{
	return get<2>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
