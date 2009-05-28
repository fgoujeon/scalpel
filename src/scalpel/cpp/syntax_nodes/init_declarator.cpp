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

#include "init_declarator.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

init_declarator::init_declarator
(
	declarator&& o0,
	optional_node<space>&& o1,
	optional_node<initializer>&& o2
):
	impl_(o0, o1, o2)
{
	add(impl_);
}

init_declarator::init_declarator
(
	head_node_t&& head,
	tail_sequence_node_t&& tail
):
	impl_(head, tail)
{
	add(impl_);
}

init_declarator::init_declarator(const init_declarator& o):
	composite_node(),
	impl_(o.impl_)
{
	add(impl_);
}

init_declarator::init_declarator(init_declarator&& o):
	composite_node(),
	impl_(o.impl_)
{
	add(impl_);
}

const init_declarator&
init_declarator::operator=(const init_declarator& o)
{
	impl_ = o.impl_;
	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes
