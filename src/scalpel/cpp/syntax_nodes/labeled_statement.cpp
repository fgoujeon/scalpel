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

#include "labeled_statement.hpp"

#include "case_statement.hpp"
#include "default_statement.hpp"
#include "classic_labeled_statement.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

labeled_statement::labeled_statement(case_statement&& o):
	impl_(new type(std::move(o)))
{
	add(*impl_);
}

labeled_statement::labeled_statement(default_statement&& o):
	impl_(new type(std::move(o)))
{
	add(*impl_);
}

labeled_statement::labeled_statement(classic_labeled_statement&& o):
	impl_(new type(std::move(o)))
{
	add(*impl_);
}

labeled_statement::labeled_statement(const labeled_statement& o):
	composite_node(),
	impl_(new type(*o.impl_))
{
	add(*impl_);
}

labeled_statement::labeled_statement(labeled_statement&& o):
	composite_node(),
	impl_(new type(*o.impl_))
{
	add(*impl_);
}

labeled_statement::~labeled_statement()
{
	delete impl_;
}

const labeled_statement&
labeled_statement::operator=(const labeled_statement& o)
{
	*impl_ = *o.impl_;
	return *this;
}

void
labeled_statement::get(boost::optional<const case_statement&>& node) const
{
	impl_->get(node);
}

void
labeled_statement::get(boost::optional<const default_statement&>& node) const
{
	impl_->get(node);
}

void
labeled_statement::get(boost::optional<const classic_labeled_statement&>& node) const
{
	impl_->get(node);
}

}}} //namespace scalpel::cpp::syntax_nodes

