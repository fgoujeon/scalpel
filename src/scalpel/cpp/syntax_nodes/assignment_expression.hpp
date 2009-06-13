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

#include <memory>
#include "common.hpp"
#include "assignment_operator.hpp"
#include "conditional_expression_fwd.hpp"
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
class assignment_expression: public composite_node
{
	public:
		class first_part;

		typedef
			list_node<first_part>
			first_part_seq
		;

		typedef
			alternative_node
			<
				conditional_expression,
				throw_expression
			>
			last_part
		;

		typedef
			sequence_node
			<
				optional_node<first_part_seq>,
				optional_node<space>,
				last_part
			>
			type
		;
		typedef type::head_node_t head_node_t;
		typedef type::tail_sequence_node_t tail_sequence_node_t;

		assignment_expression
		(
			optional_node<first_part_seq>&& o1,
			optional_node<space>&& o2,
			last_part&& o3
		);

		assignment_expression
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		);

		assignment_expression(const assignment_expression& o);

		assignment_expression(assignment_expression&& o);

		~assignment_expression();

		const assignment_expression&
		operator=(const assignment_expression& o);

	private:
		std::unique_ptr<type> impl_;
};

class assignment_expression::first_part: public composite_node
{
	public:
		typedef
			sequence_node
			<
				logical_or_expression,
				optional_node<space>,
				assignment_operator
			>
			type
		;
		typedef logical_or_expression head_node_t;
		typedef
			sequence_node
			<
				optional_node<space>,
				assignment_operator
			>
			tail_sequence_node_t
		;

		first_part
		(
			logical_or_expression&& o0,
			optional_node<space>&& o1,
			assignment_operator&& o2
		);

		first_part
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		);

		first_part(const first_part& o);

		first_part(first_part&& o);

		~first_part();

		const first_part&
		operator=(const first_part& o);

	private:
		std::unique_ptr<type> impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
