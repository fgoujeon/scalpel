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

#ifndef SCALPEL_CPP_SYNTAX_NODES_FOR_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_FOR_STATEMENT_HPP

#include "common.hpp"
#include "expression.hpp"
#include "for_init_statement.hpp"
#include "condition.hpp"
#include "statement.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
for_statement
	= "for", "(", for_init_statement, [condition], ";", [expression], ")", statement
;
\endverbatim
*/
typedef
	sequence_node
	<
		simple_text_node<str::for_>,
		optional_node<space>,
		simple_text_node<str::opening_round_bracket>,
		optional_node<space>,
		for_init_statement,
		optional_node<space>,
		optional_node<condition>,
		optional_node<space>,
		simple_text_node<str::semicolon>,
		optional_node<space>,
		optional_node<expression>,
		optional_node<space>,
		simple_text_node<str::closing_round_bracket>,
		optional_node<space>,
		statement
	>
	for_statement_t
;

class for_statement: public for_statement_t
{
	public:
		typedef for_statement_t type;
		typedef type::head_node_t head_node_t;
		typedef type::tail_sequence_node_t tail_sequence_node_t;

		for_statement
		(
			simple_text_node<str::for_>&& o0,
			optional_node<space>&& o1,
			simple_text_node<str::opening_round_bracket>&& o2,
			optional_node<space>&& o3,
			for_init_statement&& o4,
			optional_node<space>&& o5,
			optional_node<condition>&& o6,
			optional_node<space>&& o7,
			simple_text_node<str::semicolon>&& o8,
			optional_node<space>&& o9,
			optional_node<expression>&& o10,
			optional_node<space>&& o11,
			simple_text_node<str::closing_round_bracket>&& o12,
			optional_node<space>&& o13,
			statement&& o14
		):
			type
			(
				o0,
				o1,
				o2,
				o3,
				o4,
				o5,
				o6,
				o7,
				o8,
				o9,
				o10,
				o11,
				o12,
				o13,
				o14
			)
		{
		}

		for_statement
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		):
			type(head, tail)
		{
		}

		for_statement(const for_statement& o):
			type(o)
		{
		}

		for_statement(for_statement&& o):
			type(o)
		{
		}

		const for_statement&
		operator=(const for_statement& o)
		{
			*impl_ = *o.impl_;
			return *this;
		}

		const statement&
		statement_node() const
		{
			return get<14>(*this);
		}

	private:
		type* impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
