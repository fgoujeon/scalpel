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

#include "mem_initializer.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

mem_initializer::mem_initializer
(
	mem_initializer_id&& a_mem_initializer_id
):
	mem_initializer_id_(a_mem_initializer_id)
{
	update_node_list();
}

mem_initializer::mem_initializer(const mem_initializer& o):
	composite_node(),
	mem_initializer_id_(o.mem_initializer_id_)
{
	update_node_list();
}

mem_initializer::mem_initializer(mem_initializer&& o):
	mem_initializer_id_(std::move(o.mem_initializer_id_))
{
	update_node_list();
}

const mem_initializer&
mem_initializer::operator=(const mem_initializer& o)
{
	mem_initializer_id_ = o.mem_initializer_id_;
	update_node_list();

	return *this;
}

void
mem_initializer::update_node_list()
{
	clear();
	add(mem_initializer_id_);
}

}}} //namespace socoa::cpp::syntax_tree
