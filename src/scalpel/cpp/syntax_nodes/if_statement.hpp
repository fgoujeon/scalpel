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

#ifndef SCALPEL_CPP_SYNTAX_NODES_IF_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_IF_STATEMENT_HPP

#include "common.hpp"
#include "condition.hpp"
#include "statement.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
if_statement
	= "if", "(", condition, ")", statement, ["else", statement]
;
\endverbatim
*/
typedef
	sequence_node
	<
		simple_text_node<str::if_>,
		optional_node<space>,
		simple_text_node<str::opening_round_bracket>,
		optional_node<space>,
		condition,
		optional_node<space>,
		simple_text_node<str::closing_round_bracket>,
		optional_node<space>,
		statement,
		optional_node<space>,
		optional_node<simple_text_node<str::else_>>,
		optional_node<space>,
		optional_node<statement>
	>
	if_statement_t
;

class if_statement: public if_statement_t
{
	public:
		typedef if_statement_t type;
		typedef type::head_node_t head_node_t;
		typedef type::tail_sequence_node_t tail_sequence_node_t;

		if_statement
		(
			simple_text_node<str::if_>&& o0,
			optional_node<space>&& o1,
			simple_text_node<str::opening_round_bracket>&& o2,
			optional_node<space>&& o3,
			condition&& o4,
			optional_node<space>&& o5,
			simple_text_node<str::closing_round_bracket>&& o6,
			optional_node<space>&& o7,
			statement&& o8,
			optional_node<space>&& o9,
			optional_node<simple_text_node<str::else_>>&& o10,
			optional_node<space>&& o11,
			optional_node<statement>&& o12
		):
			type(o0, o1, o2, o3, o4, o5, o6, o7, o8, o9, o10, o11, o12)
		{
		}

		if_statement
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		):
			type(head, tail)
		{
		}

		if_statement(const if_statement& o):
			type(o)
		{
		}

		if_statement(if_statement&& o):
			type(o)
		{
		}

		const statement&
		statement_node() const
		{
			return get<8>(*this);
		}

		const optional_node<statement>&
		else_statement_node() const
		{
			return get<12>(*this);
		}
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
