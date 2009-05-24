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

#ifndef SCALPEL_CPP_SYNTAX_NODES_CAST_EXPRESSION_IMPL_HPP
#define SCALPEL_CPP_SYNTAX_NODES_CAST_EXPRESSION_IMPL_HPP

#include "composite_node.hpp"
#include "unary_expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef
	sequence_node
	<
		unary_expression
	>
	cast_expression_t
;

struct cast_expression_impl: public cast_expression_t
{
	typedef cast_expression_t type;
	typedef type::head_node_t head_node_t;
	typedef type::tail_sequence_node_t tail_sequence_node_t;

	cast_expression_impl
	(
		unary_expression&& unary_expression_node
	):
		type(unary_expression_node)
	{
	}

	cast_expression_impl
	(
		head_node_t&& head,
		tail_sequence_node_t&& tail
	):
		type(head, tail)
	{
	}

	cast_expression_impl(const cast_expression_impl& o):
		type(o)
	{
	}

	cast_expression_impl(cast_expression_impl&& o):
		type(o)
	{
	}

	using type::operator=;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
