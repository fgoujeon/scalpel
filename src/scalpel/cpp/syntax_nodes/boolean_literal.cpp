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

#include "boolean_literal.hpp"

#include "common_nodes.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

boolean_literal::boolean_literal(bool value):
	value_(value)
{
	update_node_list();
}

boolean_literal::boolean_literal(const boolean_literal& o):
	composite_node(),
	value_(o.value_)
{
	update_node_list();
}

boolean_literal::boolean_literal(boolean_literal&& o):
	composite_node(),
	value_(o.value_)
{
	update_node_list();
}

const boolean_literal&
boolean_literal::operator=(const boolean_literal& o)
{
	value_ = o.value_;

	update_node_list();

	return *this;
}

void
boolean_literal::update_node_list()
{
	clear();
	if(value_)
		add(global_nodes::true_keyword);
	else
		add(global_nodes::false_keyword);
}

}}} //namespace scalpel::cpp::syntax_nodes

