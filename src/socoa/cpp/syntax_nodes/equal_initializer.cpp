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

#include "equal_initializer.hpp"

#include "common_nodes.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

equal_initializer::equal_initializer
(
	boost::optional<space>&& space_node,
	initializer_clause&& initializer_clause_node
):
	space_(space_node),
	initializer_clause_(initializer_clause_node)
{
	update_node_list();
}

equal_initializer::equal_initializer(const equal_initializer& o):
	composite_node(),
	space_(o.space_),
	initializer_clause_(o.initializer_clause_)
{
	update_node_list();
}

equal_initializer::equal_initializer(equal_initializer&& o):
	composite_node(),
	space_(std::move(o.space_)),
	initializer_clause_(std::move(o.initializer_clause_))
{
	update_node_list();
}

const equal_initializer&
equal_initializer::operator=(const equal_initializer& o)
{
	space_ = o.space_;
	initializer_clause_ = o.initializer_clause_;

	update_node_list();

	return *this;
}

void
equal_initializer::update_node_list()
{
	clear();
	add(equal);
	if(space_) add(*space_);
	add(initializer_clause_);
}

}}} //namespace socoa::cpp::syntax_nodes

