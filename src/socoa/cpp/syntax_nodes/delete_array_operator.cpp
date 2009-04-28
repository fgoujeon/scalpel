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

#include "delete_array_operator.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

delete_array_operator::delete_array_operator
(
)
{
	update_node_list();
}

delete_array_operator::delete_array_operator(const delete_array_operator& o):
	composite_node()
{
	update_node_list();
}

delete_array_operator::delete_array_operator(delete_array_operator&& o):
	composite_node()
{
	update_node_list();
}

const delete_array_operator&
delete_array_operator::operator=(const delete_array_operator& o)
{
	update_node_list();

	return *this;
}

void
delete_array_operator::update_node_list()
{
	clear();
}

}}} //namespace socoa::cpp::syntax_nodes

