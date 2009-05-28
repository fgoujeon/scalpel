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

#ifndef SCALPEL_CPP_SYNTAX_NODES_EXPRESSION_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_EXPRESSION_STATEMENT_HPP

#include "common.hpp"
#include "expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
expression_statement
	= [expression], ";"
;
\endverbatim
*/
typedef
	sequence_node
	<
		optional_node<expression>,
		optional_node<space>,
		simple_text_node<str::semicolon>
	>
	expression_statement_t
;

class expression_statement: public composite_node
{
	public:
		typedef expression_statement_t type;
		typedef type::head_node_t head_node_t;
		typedef type::tail_sequence_node_t tail_sequence_node_t;

		expression_statement
		(
			optional_node<expression>&& o0,
			optional_node<space>&& o1,
			simple_text_node<str::semicolon>&& o2
		);

		expression_statement
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		);

		expression_statement(const expression_statement& o);

		expression_statement(expression_statement&& o);

		const expression_statement&
		operator=(const expression_statement& o);

	private:
		type impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
