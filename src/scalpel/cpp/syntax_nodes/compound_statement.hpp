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

#ifndef SCALPEL_CPP_SYNTAX_NODES_COMPOUND_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_COMPOUND_STATEMENT_HPP

#include "common.hpp"
#include "statement_seq.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
compound_statement
	= "{", [statement_seq], "}"
;
\endverbatim
*/
typedef
	sequence_node
	<
		simple_text_node<str::opening_brace>,
		optional_node<space>,
		optional_node<statement_seq>,
		optional_node<space>,
		simple_text_node<str::closing_brace>
	>
	compound_statement_t
;

struct compound_statement: public compound_statement_t
{
	typedef compound_statement_t type;
	typedef type::head_node_t head_node_t;
	typedef type::tail_sequence_node_t tail_sequence_node_t;

	compound_statement
	(
		simple_text_node<str::opening_brace>&& o1,
		optional_node<space>&& o2,
		optional_node<statement_seq>&& o3,
		optional_node<space>&& o4,
		simple_text_node<str::closing_brace>&& o5
	):
		type(o1, o2, o3, o4, o5)
	{
	}

	compound_statement
	(
		head_node_t&& head,
		tail_sequence_node_t&& tail
	):
		type(head, tail)
	{
	}

	compound_statement(const compound_statement& o):
		type(o)
	{
	}

	compound_statement(compound_statement&& o):
		type(o)
	{
	}

	using type::operator=;

	const optional_node<statement_seq>&
	statement_seq_node() const
	{
		return get<2, type>(*this);
	}
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
