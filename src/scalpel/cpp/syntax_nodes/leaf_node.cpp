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

#include "leaf_node.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

leaf_node::leaf_node()
{
}

leaf_node::leaf_node(const std::string& value):
	value_(value)
{
}

leaf_node::leaf_node(std::string&& value):
	value_(std::move(value))
{
}

leaf_node::leaf_node(const leaf_node& n):
	value_(n.value_)
{
}

leaf_node::leaf_node(leaf_node&& n):
	value_(std::move(n.value_))
{
}

leaf_node::~leaf_node()
{
}

node::child_const_iterator_range
leaf_node::children() const
{
	child_const_iterator first = children_.begin();
	child_const_iterator last = children_.end();

	child_const_indirect_iterator const_indirect_first(first), const_indirect_last(last);

	return child_const_iterator_range(const_indirect_first, const_indirect_last);
}

const std::string
leaf_node::value() const
{
	return value_;
}

void
leaf_node::value(const std::string& code)
{
	value_ = code;
}

void
leaf_node::value(std::string&& code)
{
	value_ = std::move(code);
}

}}} //namespace scalpel::cpp::syntax_nodes
