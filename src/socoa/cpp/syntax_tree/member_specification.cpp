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

#include "member_specification.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

member_specification::member_specification
(
	parts_t&& parts
):
	parts_(std::move(parts))
{
	update_node_list();
}

member_specification::member_specification(const member_specification& o):
	composite_node(),
	parts_(o.parts_)
{
	update_node_list();
}

member_specification::member_specification(member_specification&& o):
	parts_(std::move(o.parts_))
{
	update_node_list();
}

const member_specification&
member_specification::operator=(const member_specification& o)
{
	parts_ = o.parts_;
	update_node_list();

	return *this;
}

void
member_specification::update_node_list()
{
	clear();
	for(auto i = parts_.begin(); i != parts_.end(); ++i)
		add(*i);
}

}}} //namespace socoa::cpp::syntax_tree

