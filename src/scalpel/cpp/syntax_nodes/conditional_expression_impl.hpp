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

#ifndef SCALPEL_CPP_SYNTAX_NODES_CONDITIONAL_EXPRESSION_IMPL_HPP
#define SCALPEL_CPP_SYNTAX_NODES_CONDITIONAL_EXPRESSION_IMPL_HPP

#include <iostream>
#include "common.hpp"
#include "expressions.hpp"
#include "expression.hpp"
#include "assignment_expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
conditional_expression_impl
	= logical_or_expression, ["?", expression, ":", assignment_expression]
;
\endverbatim
*/
typedef
	sequence_node
	<
		logical_or_expression,
		optional_node<space>,
		optional_node<simple_text_node<str::question_mark>>,
		optional_node<space>,
		optional_node<expression>,
		optional_node<space>,
		optional_node<simple_text_node<str::colon>>,
		optional_node<space>,
		optional_node<assignment_expression>
	>
	conditional_expression_t
;

struct conditional_expression_impl: public conditional_expression_t
{
	typedef logical_or_expression head_node_t;
	typedef conditional_expression_t::tail_sequence_node_t tail_sequence_node_t;

	conditional_expression_impl
	(
		logical_or_expression&& o1,
		optional_node<space>&& o2,
		optional_node<simple_text_node<str::question_mark>> o3,
		optional_node<space>&& o4,
		optional_node<expression>&& o5,
		optional_node<space>&& o6,
		optional_node<simple_text_node<str::colon>> o7,
		optional_node<space>&& o8,
		optional_node<assignment_expression>&& o9
	):
		conditional_expression_t(o1, o2, o3, o4, o5, o6, o7, o8, o9)
	{
	}

	conditional_expression_impl
	(
		head_node_t&& n,
		tail_sequence_node_t&& seq
	):
		conditional_expression_t(n, seq)
	{
	}

	conditional_expression_impl(const conditional_expression_impl& o):
		conditional_expression_t(static_cast<const conditional_expression_t&>(o))
	{
	}

	conditional_expression_impl(conditional_expression_impl&& o):
		conditional_expression_t(static_cast<conditional_expression_t&&>(o))
	{
	}

	conditional_expression_impl(const conditional_expression_t& o):
		conditional_expression_t(o)
	{
	}

	using conditional_expression_t::operator=;
};

struct conditional_expression_tail_sequence_node: public conditional_expression_impl::tail_sequence_node_t
{
	typedef conditional_expression_impl::tail_sequence_node_t type;
	typedef conditional_expression_t::tail_sequence_node_t::head_node_t head_node_t;
	typedef conditional_expression_t::tail_sequence_node_t::tail_sequence_node_t tail_sequence_node_t;

	conditional_expression_tail_sequence_node
	(
		optional_node<space>&& o2,
		optional_node<simple_text_node<str::question_mark>> o3,
		optional_node<space>&& o4,
		optional_node<expression>&& o5,
		optional_node<space>&& o6,
		optional_node<simple_text_node<str::colon>> o7,
		optional_node<space>&& o8,
		optional_node<assignment_expression>&& o9
	):
		type(o2, o3, o4, o5, o6, o7, o8, o9)
	{
	}

	conditional_expression_tail_sequence_node
	(
		head_node_t&& n,
		tail_sequence_node_t&& seq
	):
		type(n, seq)
	{
	}

	conditional_expression_tail_sequence_node(const conditional_expression_tail_sequence_node& o):
		type(static_cast<const type&>(o))
	{
	}

	conditional_expression_tail_sequence_node(conditional_expression_tail_sequence_node&& o):
		type(static_cast<type&&>(o))
	{
	}

	conditional_expression_tail_sequence_node(const type& o):
		type(o)
	{
	}

	using type::operator=;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
