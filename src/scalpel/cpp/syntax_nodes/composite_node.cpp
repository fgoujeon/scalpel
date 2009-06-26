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

#include "composite_node.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

composite_node::composite_node()
{
}

composite_node::~composite_node()
{
}

node::child_const_iterator_range
composite_node::children() const
{
	child_const_iterator first = children_.begin();
	child_const_iterator last = children_.end();

	child_const_indirect_iterator const_indirect_first(first), const_indirect_last(last);

	return child_const_iterator_range(const_indirect_first, const_indirect_last);
}

const std::string
composite_node::value() const
{
	std::string code;
	for(children_t::const_iterator i = children_.begin(); i != children_.end(); ++i)
	{
		const node& child_node = **i;
		code += child_node.value();
	}
	return code;
}

void
composite_node::add(const node& a_node)
{
	children_.push_back(&a_node);
}

void
composite_node::push_front(const node& n)
{
	children_.push_front(&n);
}

void
composite_node::clear()
{
	children_.clear();
}

}}} //namespace scalpel::cpp::syntax_nodes
