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

#ifndef SCALPEL_CPP_SYNTAX_NODES_CAST_EXPRESSION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_CAST_EXPRESSION_HPP

#include <memory>
#include "common.hpp"
#include "type_id.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class unary_expression;

typedef
	sequence_node
	<
		predefined_text_node<str::opening_round_bracket>,
		optional_node<space>,
		type_id,
		optional_node<space>,
		predefined_text_node<str::closing_round_bracket>
	>
	cast_expression_first_part
;

typedef
	list_node
	<
		cast_expression_first_part
	>
	cast_expression_first_part_seq
;

typedef
	sequence_node
	<
		optional_node<cast_expression_first_part_seq>,
		optional_node<space>,
		unary_expression
	>
	cast_expression_t
;

typedef
	sequence_node
	<
		optional_node<space>,
		unary_expression
	>
	cast_expression_tail_t
;


/**
cast_expression
	= unary_expression
	| !(cast_expression_first_part_seq >> !s) >> unary_expression
;
cast_expression_first_part_seq
	= cast_expression_first_part % !s
;
cast_expression_first_part
	= '(' >> !s >> type_id >> !s >> ')'
;
*/
class cast_expression: public composite_node
{
	public:
		typedef cast_expression_t type;
		typedef optional_node<cast_expression_first_part_seq> head_node_t;
		typedef cast_expression_tail_t tail_sequence_node_t;

		typedef cast_expression_first_part first_part;
		typedef cast_expression_first_part_seq first_part_seq;

		cast_expression
		(
			optional_node<cast_expression_first_part_seq>&& o0,
			optional_node<space>&& o1,
			unary_expression&& o2
		);

		cast_expression
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		);

		cast_expression(const cast_expression& o);

		cast_expression(cast_expression&& o);

		~cast_expression();

		const cast_expression&
		operator=(const cast_expression& o);

	private:
		std::unique_ptr<type> impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
