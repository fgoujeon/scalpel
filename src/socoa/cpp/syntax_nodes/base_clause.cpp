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

#include "base_clause.hpp"

#include "common_nodes.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

base_clause::base_clause
(
	boost::optional<space>&& space_node,
	base_specifier_list&& a_base_specifier_list
):
	space_(space_node),
    base_specifier_list_(a_base_specifier_list)
{
	update_node_list();
}

base_clause::base_clause(const base_clause& o):
	composite_node(),
	space_(o.space_),
    base_specifier_list_(o.base_specifier_list_)
{
	update_node_list();
}

base_clause::base_clause(base_clause&& o):
	space_(std::move(o.space_)),
    base_specifier_list_(std::move(o.base_specifier_list_))
{
	update_node_list();
}

const base_clause&
base_clause::operator=(const base_clause& o)
{
	space_ = o.space_;
	base_specifier_list_ = o.base_specifier_list_;

	update_node_list();

	return *this;
}

void
base_clause::update_node_list()
{
	clear();
	add(semicolon);
	if(space_) add(*space_);
	add(base_specifier_list_);
}

}}} //namespace socoa::cpp::syntax_nodes
