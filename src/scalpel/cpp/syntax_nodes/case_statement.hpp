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

#ifndef SCALPEL_CPP_SYNTAX_NODES_CASE_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_CASE_STATEMENT_HPP

#include "common.hpp"
#include "conditional_expression.hpp"
#include "statement.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef
	sequence_node
	<
		predefined_text_node<str::case_>,
		optional_node<space>,
		conditional_expression,
		optional_node<space>,
		predefined_text_node<str::colon>,
		optional_node<space>,
		statement
	>
	case_statement_t
;

/**
\verbatim
case_statement
	= str_p("case") >> !s >> conditional_expression >> !s >> ':' >> !s >> statement
;
\endverbatim
*/
struct case_statement: public case_statement_t
{
	typedef case_statement_t type;
	typedef case_statement_t::head_node_t head_node_t;
	typedef case_statement_t::tail_sequence_node_t tail_sequence_node_t;

	case_statement
	(
		predefined_text_node<str::case_>&& o1,
		optional_node<space>&& o2,
		conditional_expression&& o3,
		optional_node<space>&& o4,
		predefined_text_node<str::colon>&& o5,
		optional_node<space>&& o6,
		statement&& o7
	):
		case_statement_t(o1, o2, o3, o4, o5, o6, o7)
	{
	}

	case_statement
	(
		head_node_t&& head,
		tail_sequence_node_t&& tail
	):
		case_statement_t(head, tail)
	{
	}

	case_statement
	(
		case_statement_t&& o
	):
		case_statement_t(std::move(o))
	{
	}

	case_statement(const case_statement& o):
		case_statement_t(o)
	{
	}

	case_statement(case_statement&& o):
		case_statement_t(o)
	{
	}

	using case_statement_t::operator=;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
