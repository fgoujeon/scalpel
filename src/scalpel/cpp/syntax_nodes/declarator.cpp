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

#include "ptr_operator_seq.hpp"
#include "direct_declarator.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

declarator::declarator
(
	optional_node<ptr_operator_seq>&& o1,
	optional_node<space>&& o2,
    direct_declarator&& o3
):
	impl_(new type(o1, o2, o3))
{
}

declarator::declarator
(
	head_node_t&& head,
	tail_sequence_node_t&& tail
):
	impl_(new type(head, tail))
{
}

declarator::declarator(const declarator& o):
	impl_(new type(*o.impl_))
{
}

declarator::declarator(declarator&& o):
	impl_(std::move(o.impl_))
{
}

declarator::~declarator()
{
}

const declarator&
declarator::operator=(const declarator& o)
{
	*impl_ = *o.impl_;
	return *this;
}

node::child_const_iterator_range
declarator::children() const
{
	return impl_->children();
}

const std::string
declarator::value() const
{
	return impl_->value();
}

const declarator::tail_sequence_node_t&
declarator::tail() const
{
	return impl_->tail();
}



const direct_declarator&
get_direct_declarator(const declarator& o)
{
	return get<2>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes
