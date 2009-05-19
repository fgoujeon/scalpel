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

#include "statement_impl.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

statement_impl::statement_impl(labeled_statement&& o):
	statement_t(std::move(o))
{
}

statement_impl::statement_impl(expression_statement&& o):
	statement_t(std::move(o))
{
}

statement_impl::statement_impl(compound_statement&& o):
	statement_t(std::move(o))
{
}

statement_impl::statement_impl(selection_statement&& o):
	statement_t(std::move(o))
{
}

statement_impl::statement_impl(iteration_statement&& o):
	statement_t(std::move(o))
{
}

statement_impl::statement_impl(jump_statement&& o):
	statement_t(std::move(o))
{
}

statement_impl::statement_impl(block_declaration&& o):
	statement_t(std::move(o))
{
}

statement_impl::statement_impl(try_block&& o):
	statement_t(std::move(o))
{
}

statement_impl::statement_impl(const statement_impl& o):
	statement_t(static_cast<const statement_t&>(o))
{
}

statement_impl::statement_impl(statement_impl&& o):
	statement_t(static_cast<statement_t&&>(o))
{
}

}}} //namespace scalpel::cpp::syntax_nodes

