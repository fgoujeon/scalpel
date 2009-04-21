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

#include "continue_statement.hpp"

#include "common_nodes.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

continue_statement::continue_statement
(
	boost::optional<space>&& space_node
):
	space_(space_node)
{
	update_node_list();
}

continue_statement::continue_statement(const continue_statement& o):
	composite_node(),
	space_(o.space_)
{
	update_node_list();
}

continue_statement::continue_statement(continue_statement&& o):
	composite_node(),
	space_(std::move(o.space_))
{
	update_node_list();
}

const continue_statement&
continue_statement::operator=(const continue_statement& o)
{
	space_ = o.space_;

	update_node_list();

	return *this;
}

void
continue_statement::update_node_list()
{
	clear();

	add(continue_keyword);
	if(space_) add(*space_);
	add(semicolon);
}

}}} //namespace socoa::cpp::syntax_tree

