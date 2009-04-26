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

#include "case_statement.hpp"

#include "common_nodes.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

case_statement::case_statement
(
)
{
	update_node_list();
}

case_statement::case_statement(const case_statement& o):
	composite_node()
{
	update_node_list();
}

case_statement::case_statement(case_statement&& o):
	composite_node()
{
	update_node_list();
}

const case_statement&
case_statement::operator=(const case_statement& o)
{
	update_node_list();

	return *this;
}

void
case_statement::update_node_list()
{
	clear();
	add(case_keyword);
	add(colon);
}

}}} //namespace socoa::cpp::syntax_nodes

