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

#include "selection_statement.hpp"

#include "selection_statement_impl.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

selection_statement::selection_statement(if_statement&& o):
	impl_(new selection_statement_impl(std::move(o)))
{
	add(*impl_);
}

selection_statement::selection_statement(switch_statement&& o):
	impl_(new selection_statement_impl(std::move(o)))
{
	add(*impl_);
}

selection_statement::selection_statement(const selection_statement& o):
	composite_node(),
	impl_(new selection_statement_impl(*o.impl_))
{
	add(*impl_);
}

selection_statement::selection_statement(selection_statement&& o):
	composite_node(),
	impl_(new selection_statement_impl(*o.impl_))
{
	add(*impl_);
}

selection_statement::~selection_statement()
{
	delete impl_;
}

const selection_statement&
selection_statement::operator=(const selection_statement& o)
{
	*impl_ = *o.impl_;
	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes

