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

#include "new_array_operator.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

new_array_operator::new_array_operator
(
)
{
	update_node_list();
}

new_array_operator::new_array_operator(const new_array_operator& o):
	composite_node()
{
	update_node_list();
}

new_array_operator::new_array_operator(new_array_operator&& o):
	composite_node()
{
	update_node_list();
}

const new_array_operator&
new_array_operator::operator=(const new_array_operator& o)
{
	update_node_list();

	return *this;
}

void
new_array_operator::update_node_list()
{
	clear();
}

}}} //namespace scalpel::cpp::syntax_nodes

