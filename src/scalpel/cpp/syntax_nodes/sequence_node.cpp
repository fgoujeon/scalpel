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

#include "sequence_node.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

sequence_node<>::sequence_node()
{
}

sequence_node<>::sequence_node(const sequence_node&)
{
}

sequence_node<>::sequence_node(sequence_node&&)
{
}

const sequence_node<>&
sequence_node<>::operator=(const sequence_node&)
{
	return *this;
}

node::child_const_iterator_range
sequence_node<>::children() const
{
	return children_;
}

void
sequence_node<>::push_front(const node& n)
{
	children_.push_front(&n);
}

const std::string
sequence_node<>::value() const
{
	std::string code;
	for(children_t::const_iterator i = children_.begin(); i != children_.end(); ++i)
	{
		const node& child_node = **i;
		code += child_node.value();
	}
	return code;
}

}}} //namespace scalpel::cpp::syntax_nodes

