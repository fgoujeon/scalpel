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

#include "iteration_statement.hpp"

#include "iteration_statement_impl.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

iteration_statement::iteration_statement(while_statement&& o):
	impl_(new iteration_statement_impl(std::move(o)))
{
	add(*impl_);
}

iteration_statement::iteration_statement(do_while_statement&& o):
	impl_(new iteration_statement_impl(std::move(o)))
{
	add(*impl_);
}

iteration_statement::iteration_statement(for_statement&& o):
	impl_(new iteration_statement_impl(std::move(o)))
{
	add(*impl_);
}

iteration_statement::iteration_statement(const iteration_statement& o):
	composite_node(),
	impl_(new iteration_statement_impl(*o.impl_))
{
	add(*impl_);
}

iteration_statement::iteration_statement(iteration_statement&& o):
	composite_node(),
	impl_(new iteration_statement_impl(*o.impl_))
{
	add(*impl_);
}

iteration_statement::~iteration_statement()
{
	delete impl_;
}

const iteration_statement&
iteration_statement::operator=(const iteration_statement& o)
{
	*impl_ = *o.impl_;
	return *this;
}

void
iteration_statement::get(boost::optional<const while_statement&>& node) const
{
	impl_->get(node);
}

void
iteration_statement::get(boost::optional<const do_while_statement&>& node) const
{
	impl_->get(node);
}

void
iteration_statement::get(boost::optional<const for_statement&>& node) const
{
	impl_->get(node);
}

}}} //namespace scalpel::cpp::syntax_nodes

