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

#include "qualified_template_id.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

qualified_template_id::qualified_template_id
(
    template_id&& a_template_id
):
    template_id_(std::move(a_template_id))
{
	update_node_list();
}

qualified_template_id::qualified_template_id(const qualified_template_id& o):
	composite_node(),
    template_id_(o.template_id_)
{
	update_node_list();
}

qualified_template_id::qualified_template_id(qualified_template_id&& o):
    template_id_(std::move(o.template_id_))
{
	update_node_list();
}

const qualified_template_id&
qualified_template_id::operator=(const qualified_template_id& o)
{
    template_id_ = o.template_id_;
	update_node_list();

	return *this;
}

void
qualified_template_id::update_node_list()
{
	clear();
	add(template_id_);
}

}}} //namespace scalpel::cpp::syntax_nodes
