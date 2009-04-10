/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "composite_node.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

composite_node::composite_node()
{
}

composite_node::composite_node(composite_node&& n):
	node(std::move(n)),
	nodes_(std::move(n.nodes_))
{
}

composite_node::~composite_node()
{
}

const std::string
composite_node::raw_code() const
{
	std::string code;
	for(nodes_t::const_iterator i = nodes_.begin(); i != nodes_.end(); ++i)
	{
		const node& child_node = **i;
		code += child_node.raw_code();
	}
	return code;
}

void
composite_node::add(node& a_node)
{
	nodes_.push_back(&a_node);
}

}}} //namespace socoa::cpp::syntax_tree
