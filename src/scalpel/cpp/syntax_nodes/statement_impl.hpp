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

#ifndef SCALPEL_CPP_SYNTAX_NODES_STATEMENT_IMPL_HPP
#define SCALPEL_CPP_SYNTAX_NODES_STATEMENT_IMPL_HPP

#include "alternative_node.hpp"
#include "labeled_statement.hpp"
#include "expression_statement.hpp"
#include "compound_statement.hpp"
#include "selection_statement.hpp"
#include "iteration_statement.hpp"
#include "jump_statement.hpp"
#include "block_declaration.hpp"
#include "try_block.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef
	alternative_node
	<
		labeled_statement,
		expression_statement,
		compound_statement,
		selection_statement,
		iteration_statement,
		jump_statement,
		block_declaration,
		try_block
	>
	statement_t
;

struct statement_impl: public statement_t
{
	typedef statement_t type;
	typedef type::head_node_t head_node_t;
	typedef type::tail_alternative_node_t tail_alternative_node_t;

	statement_impl(labeled_statement&& o);

	statement_impl(expression_statement&& o);

	statement_impl(compound_statement&& o);

	statement_impl(selection_statement&& o);

	statement_impl(iteration_statement&& o);

	statement_impl(jump_statement&& o);

	statement_impl(block_declaration&& o);

	statement_impl(try_block&& o);

	statement_impl(const statement_impl& o);

	statement_impl(statement_impl&& o);

	using type::get;
};

struct statement_tail: public statement_t::tail_alternative_node_t
{
	typedef statement_t::tail_alternative_node_t type;
	typedef type::head_node_t head_node_t;
	typedef type::tail_alternative_node_t tail_alternative_node_t;

	statement_tail(expression_statement&& o):
		type(o)
	{
	}

	statement_tail(compound_statement&& o):
		type(o)
	{
	}

	statement_tail(selection_statement&& o):
		type(o)
	{
	}

	statement_tail(iteration_statement&& o):
		type(o)
	{
	}

	statement_tail(jump_statement&& o):
		type(o)
	{
	}

	statement_tail(block_declaration&& o):
		type(o)
	{
	}

	statement_tail(try_block&& o):
		type(o)
	{
	}

	statement_tail(const statement_tail& o):
		type(static_cast<const type&>(o))
	{
	}

	statement_tail(statement_tail&& o):
		type(static_cast<type&&>(o))
	{
	}

	using type::get;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
