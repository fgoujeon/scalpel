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

#ifndef SCALPEL_CPP_SYNTAX_NODES_DO_WHILE_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_DO_WHILE_STATEMENT_HPP

#include "common.hpp"
#include "statement.hpp"
#include "expression.hpp"

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
		simple_text_node<str::do_>,
		optional_node<space>,
		statement,
		optional_node<space>,
		simple_text_node<str::while_>,
		optional_node<space>,
		simple_text_node<str::opening_round_bracket>,
		optional_node<space>,
		expression,
		optional_node<space>,
		simple_text_node<str::closing_round_bracket>,
		optional_node<space>,
		simple_text_node<str::semicolon>
	>
	do_while_statement_t
;

struct do_while_statement: public do_while_statement_t
{
	typedef do_while_statement_t type;
	typedef type::head_node_t head_node_t;
	typedef type::tail_sequence_node_t tail_sequence_node_t;

	do_while_statement
	(
		head_node_t&& head,
		tail_sequence_node_t&& tail
	):
		type(head, tail)
	{
	}

	do_while_statement
	(
		const do_while_statement& o
	):
		type(o)
	{
	}

	do_while_statement
	(
		do_while_statement&& o
	):
		type(o)
	{
	}

	using type::operator=;

	const statement&
	statement_node() const
	{
		return get<2, type>(*this);
	}
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
