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

#include "break_statement.hpp"

#include "common_nodes.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

break_statement::break_statement
(
	optional_node<space>&& space_node
):
	space_(space_node)
{
	update_node_list();
}

break_statement::break_statement(const break_statement& o):
	composite_node(),
	space_(o.space_)
{
	update_node_list();
}

break_statement::break_statement(break_statement&& o):
	composite_node(),
	space_(std::move(o.space_))
{
	update_node_list();
}

const break_statement&
break_statement::operator=(const break_statement& o)
{
	space_ = o.space_;

	update_node_list();

	return *this;
}

void
break_statement::update_node_list()
{
	clear();

	add(common_nodes::break_keyword);
	if(space_) add(*space_);
	add(common_nodes::semicolon);
}

}}} //namespace scalpel::cpp::syntax_nodes

