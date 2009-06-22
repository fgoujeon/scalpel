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

#ifndef SCALPEL_CPP_SYNTAX_NODES_WHILE_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_WHILE_STATEMENT_HPP

#include "common.hpp"
#include "condition.hpp"
#include "statement.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
while_statement
	= str_p("while") >> !s >> '(' >> !s >> condition >> !s >> ')' >> !s >> statement
;
*/
typedef
	sequence_node
	<
		predefined_text_node<str::while_>,
		optional_node<space>,
		predefined_text_node<str::opening_round_bracket>,
		optional_node<space>,
		condition,
		optional_node<space>,
		predefined_text_node<str::closing_round_bracket>,
		optional_node<space>,
		statement
	>
	while_statement_t
;

struct while_statement: public while_statement_t
{
	typedef while_statement_t type;
	typedef type::head_node_t head_node_t;
	typedef type::tail_sequence_node_t tail_sequence_node_t;

	while_statement
	(
		predefined_text_node<str::while_>&& o1,
		optional_node<space>&& o2,
		predefined_text_node<str::opening_round_bracket>&& o3,
		optional_node<space>&& o4,
		condition&& o5,
		optional_node<space>&& o6,
		predefined_text_node<str::closing_round_bracket>&& o7,
		optional_node<space>&& o8,
		statement&& o9
	):
		type(o1, o2, o3, o4, o5, o6, o7, o8, o9)
	{
	}

	while_statement
	(
		head_node_t&& head,
		tail_sequence_node_t&& tail
	):
		type(head, tail)
	{
	}

	while_statement(const while_statement& o):
		type(o)
	{
	}

	while_statement(while_statement&& o):
		type(o)
	{
	}
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
