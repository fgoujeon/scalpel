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

#ifndef SCALPEL_CPP_SYNTAX_NODES_ITERATION_STATEMENT_IMPL_HPP
#define SCALPEL_CPP_SYNTAX_NODES_ITERATION_STATEMENT_IMPL_HPP

#include "while_statement.hpp"
#include "do_while_statement.hpp"
#include "for_statement.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef
	alternative_node
	<
		while_statement,
		do_while_statement,
		for_statement
	>
	iteration_statement_t
;

struct iteration_statement_impl: public iteration_statement_t
{
	explicit
	iteration_statement_impl(while_statement&& o);

	explicit
	iteration_statement_impl(do_while_statement&& o);

	explicit
	iteration_statement_impl(for_statement&& o);

	iteration_statement_impl(const iteration_statement_impl& o);

	iteration_statement_impl(iteration_statement_impl&& o);
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
