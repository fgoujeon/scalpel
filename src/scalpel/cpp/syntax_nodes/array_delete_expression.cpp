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

#include "array_delete_expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

array_delete_expression::array_delete_expression
(
)
{
	update_node_list();
}

array_delete_expression::array_delete_expression(const array_delete_expression& o):
	composite_node()
{
	update_node_list();
}

array_delete_expression::array_delete_expression(array_delete_expression&& o):
	composite_node()
{
	update_node_list();
}

const array_delete_expression&
array_delete_expression::operator=(const array_delete_expression& o)
{
	update_node_list();

	return *this;
}

void
array_delete_expression::update_node_list()
{
	clear();
}

}}} //namespace scalpel::cpp::syntax_nodes

