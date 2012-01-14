/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_SYNTAX_NODES_UNARY_OPERATOR_EXPRESSION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_UNARY_OPERATOR_EXPRESSION_HPP

#include "unary_operator.hpp"
#include "cast_expression.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
unary_operator_unary_expression
	= unary_operator, cast_expression
;
\endverbatim
*/
typedef
	sequence_node
	<
		unary_operator,
		cast_expression
	>
	unary_operator_expression
;

inline
const unary_operator&
get_operator(const unary_operator_expression& o)
{
	return get<0>(o);
}

inline
const cast_expression&
get_operand(const unary_operator_expression& o)
{
	return get<1>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif

