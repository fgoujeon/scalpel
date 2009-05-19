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

#ifndef SCALPEL_CPP_SYNTAX_NODES_SELECTION_STATEMENT_IMPL_HPP
#define SCALPEL_CPP_SYNTAX_NODES_SELECTION_STATEMENT_IMPL_HPP

#include "alternative_node.hpp"
#include "if_statement.hpp"
#include "switch_statement.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef
	alternative_node
	<
		if_statement,
		switch_statement
	>
	selection_statement_t
;

struct selection_statement_impl: public selection_statement_t
{
	explicit
	selection_statement_impl(if_statement&& o);

	explicit
	selection_statement_impl(switch_statement&& o);

	selection_statement_impl(const selection_statement_impl& o);

	selection_statement_impl(selection_statement_impl&& o);
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
