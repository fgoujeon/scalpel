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

#include "declarator.hpp"

#include "declarator_impl.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

declarator::declarator
(
	optional_node<ptr_operator_seq>&& o1,
	optional_node<space>&& o2,
    direct_declarator&& o3
):
	impl_(new declarator_impl(o1, o2, o3))
{
	add(*impl_);
}

declarator::declarator
(
	head_node_t&& head,
	tail_sequence_node_t&& tail
):
	impl_(new declarator_impl(head, tail))
{
}

declarator::declarator(const declarator& o):
	composite_node(),
	impl_(new declarator_impl(*o.impl_))
{
	add(*impl_);
}

declarator::declarator(declarator&& o):
	composite_node(),
	impl_(o.impl_)
{
	assert(o.impl_);
	o.impl_ = 0;
	add(*impl_);
}

declarator::~declarator()
{
	delete impl_;
}

const declarator&
declarator::operator=(const declarator& o)
{
	assert(impl_);
	assert(o.impl_);
	*impl_ = *o.impl_;
	return *this;
}

const direct_declarator&
declarator::direct_declarator_node() const
{
	assert(impl_);
	return impl_->direct_declarator_node();
}

}}} //namespace scalpel::cpp::syntax_nodes
