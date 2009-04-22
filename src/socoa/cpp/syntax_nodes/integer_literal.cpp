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

#include "integer_literal.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

integer_literal::integer_literal
(
	std::string&& value
):
	value_(value)
{
	update_node_list();
}

integer_literal::integer_literal(const integer_literal& o):
	composite_node(),
	value_(o.value_)
{
	update_node_list();
}

integer_literal::integer_literal(integer_literal&& o):
	composite_node(),
	value_(std::move(o.value_))
{
	update_node_list();
}

const integer_literal&
integer_literal::operator=(const integer_literal& o)
{
	value_ = o.value_;

	update_node_list();

	return *this;
}

void
integer_literal::update_node_list()
{
	clear();
	add(value_);
}

}}} //namespace socoa::cpp::syntax_nodes

