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

#include "type_id_sizeof_expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

type_id_sizeof_expression::type_id_sizeof_expression
(
)
{
	update_node_list();
}

type_id_sizeof_expression::type_id_sizeof_expression(const type_id_sizeof_expression& o):
	composite_node()
{
	update_node_list();
}

type_id_sizeof_expression::type_id_sizeof_expression(type_id_sizeof_expression&& o):
	composite_node()
{
	update_node_list();
}

const type_id_sizeof_expression&
type_id_sizeof_expression::operator=(const type_id_sizeof_expression& o)
{
	update_node_list();

	return *this;
}

void
type_id_sizeof_expression::update_node_list()
{
	clear();
}

}}} //namespace scalpel::cpp::syntax_nodes

