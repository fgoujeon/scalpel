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

#ifndef SCALPEL_CPP_SYNTAX_NODES_UNARY_SIZEOF_EXPRESSION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_UNARY_SIZEOF_EXPRESSION_HPP

#include <memory>
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class unary_expression;

typedef
	sequence_node
	<
		predefined_text_node<str::sizeof_>,
		optional_node<space>,
		unary_expression
	>
	unary_sizeof_expression_t
;

typedef
	sequence_node
	<
		optional_node<space>,
		unary_expression
	>
	unary_sizeof_expression_tail_t
;

/**
unary_sizeof_expression
	= str_p("sizeof") >> !s >> unary_expression
;
*/
class unary_sizeof_expression: public composite_node
{
	public:
		typedef unary_sizeof_expression_t type;
		typedef predefined_text_node<str::sizeof_> head_node_t;
		typedef unary_sizeof_expression_tail_t tail_sequence_node_t;

		unary_sizeof_expression
		(
			predefined_text_node<str::sizeof_>&& o0,
			optional_node<space>&& o1,
			unary_expression&& o2
		);

		unary_sizeof_expression
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		);

		unary_sizeof_expression(const unary_sizeof_expression& o);

		unary_sizeof_expression(unary_sizeof_expression&& o);

		~unary_sizeof_expression();

		const unary_sizeof_expression&
		operator=(const unary_sizeof_expression& o);

	private:
		std::unique_ptr<type> impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
