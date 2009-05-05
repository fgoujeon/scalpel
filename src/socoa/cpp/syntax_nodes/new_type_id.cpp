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

#include "new_type_id.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

new_type_id::new_type_id
(
)
{
	update_node_list();
}

new_type_id::new_type_id(const new_type_id& o):
	composite_node()
{
	update_node_list();
}

new_type_id::new_type_id(new_type_id&& o):
	composite_node()
{
	update_node_list();
}

const new_type_id&
new_type_id::operator=(const new_type_id& o)
{
	update_node_list();

	return *this;
}

void
new_type_id::update_node_list()
{
	clear();
}

}}} //namespace socoa::cpp::syntax_nodes

