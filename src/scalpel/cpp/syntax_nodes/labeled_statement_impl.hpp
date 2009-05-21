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

#ifndef SCALPEL_CPP_SYNTAX_NODES_LABELED_STATEMENT_IMPL_HPP
#define SCALPEL_CPP_SYNTAX_NODES_LABELED_STATEMENT_IMPL_HPP

#include "alternative_node.hpp"
#include "case_statement.hpp"
#include "default_statement.hpp"
#include "classic_labeled_statement.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef
	alternative_node
	<
		case_statement,
		default_statement,
		classic_labeled_statement
	>
	labeled_statement_t
;

struct labeled_statement_impl: public labeled_statement_t
{
	typedef labeled_statement_t type;
	typedef type::head_node_t head_node_t;
	typedef type::tail_alternative_node_t tail_alternative_node_t;

	labeled_statement_impl(case_statement&& o);

	labeled_statement_impl(default_statement&& o);

	labeled_statement_impl(classic_labeled_statement&& o);

	labeled_statement_impl(const labeled_statement_impl& o);

	labeled_statement_impl(labeled_statement_impl&& o);

	using type::get;
};

struct labeled_statement_tail: public labeled_statement_t::tail_alternative_node_t
{
	typedef labeled_statement_t::tail_alternative_node_t type;
	typedef type::head_node_t head_node_t;
	typedef type::tail_alternative_node_t tail_alternative_node_t;

	labeled_statement_tail(default_statement&& o):
		type(o)
	{
	}

	labeled_statement_tail(classic_labeled_statement&& o):
		type(o)
	{
	}

	labeled_statement_tail(const labeled_statement_tail& o):
		type(static_cast<const type&>(o))
	{
	}

	labeled_statement_tail(labeled_statement_tail&& o):
		type(static_cast<type&&>(o))
	{
	}

	using type::get;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
