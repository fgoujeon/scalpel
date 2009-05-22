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

#ifndef SCALPEL_CPP_SYNTAX_NODES_ASSIGNMENT_EXPRESSION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_ASSIGNMENT_EXPRESSION_HPP

#include "common.hpp"
#include "assignment_operator.hpp"
#include "conditional_expression.hpp"
#include "expressions.hpp"
#include "throw_expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
assignment_expression
	= [assignment_expression_first_part_seq], assignment_expression_last_part
;
assignment_expression::first_part_seq
	= {assignment_expression::first_part}
;
assignment_expression::first_part
	= logical_or_expression, assignment_operator
;
assignment_expression_last_part
	= conditional_expression
	| throw_expression
;
\endverbatim
*/
typedef
	sequence_node
	<
		logical_or_expression,
		optional_node<space>,
		assignment_operator
	>
	assignment_expression_first_part
;

typedef
	list_node
	<
		assignment_expression_first_part
	>
	assignment_expression_first_part_seq
;

typedef
	alternative_node
	<
		conditional_expression,
		throw_expression
	>
	assignment_expression_last_part
;

typedef
	sequence_node
	<
		optional_node<assignment_expression_first_part_seq>,
		optional_node<space>,
		assignment_expression_last_part
	>
	assignment_expression_t
;

struct assignment_expression: public assignment_expression_t
{
	typedef assignment_expression_t type;
	typedef type::head_node_t head_node_t;
	typedef type::tail_sequence_node_t tail_sequence_node_t;

	typedef assignment_expression_first_part first_part;
	typedef assignment_expression_first_part_seq first_part_seq;
	typedef assignment_expression_last_part last_part;

	assignment_expression
	(
		optional_node<assignment_expression_first_part_seq>&& o1,
		optional_node<space>&& o2,
		assignment_expression_last_part&& o3
	):
		type(o1, o2, o3)
	{
	}

	assignment_expression
	(
		head_node_t&& head,
		tail_sequence_node_t&& tail
	):
		type(head, tail)
	{
	}

	assignment_expression(const assignment_expression& o):
		type(o)
	{
	}

	assignment_expression(assignment_expression&& o):
		type(o)
	{
	}

	using type::operator=;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
