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

#ifndef SCALPEL_CPP_SYNTAX_NODES_DECLARATOR_IMPL_HPP
#define SCALPEL_CPP_SYNTAX_NODES_DECLARATOR_IMPL_HPP

#include <memory>
#include <vector>
#include "composite_node.hpp"
#include "ptr_operator_seq.hpp"
#include "direct_declarator.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
declarator_impl
	= {ptr_operator}, direct_declarator
;
\endverbatim
*/
typedef
	sequence_node
	<
		optional_node<ptr_operator_seq>,
		optional_node<space>,
		direct_declarator
	>
	declarator_t
;

struct declarator_impl: public declarator_t
{
	typedef declarator_t type;
	typedef type::head_node_t head_node_t;
	typedef type::tail_sequence_node_t tail_sequence_node_t;

	declarator_impl
	(
		optional_node<ptr_operator_seq>&& o1,
		optional_node<space>&& o2,
		direct_declarator&& o3
	):
		type(o1, o2, o3)
	{
	}

	declarator_impl
	(
		head_node_t head,
		tail_sequence_node_t tail
	):
		type(head, tail)
	{
	}

	declarator_impl(const declarator_impl& o):
		type(o)
	{
	}

	declarator_impl(declarator_impl&& o):
		type(o)
	{
	}

	const direct_declarator&
	direct_declarator_node() const
	{
		return get<2>(*this);
	}
};

struct declarator_tail: public declarator_t::tail_sequence_node_t
{
	typedef declarator_t::tail_sequence_node_t type;
	typedef type::head_node_t head_node_t;
	typedef type::tail_sequence_node_t tail_sequence_node_t;

	declarator_tail
	(
		optional_node<space>&& o2,
		direct_declarator&& o3
	):
		type(o2, o3)
	{
	}

	declarator_tail
	(
		head_node_t head,
		tail_sequence_node_t tail
	):
		type(head, tail)
	{
	}

	declarator_tail(const declarator_tail& o):
		type(o)
	{
	}

	declarator_tail(declarator_tail&& o):
		type(o)
	{
	}
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
