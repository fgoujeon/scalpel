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

#include "template_declaration.hpp"

#include "declaration.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

template_declaration::template_declaration
(
    bool export_keyword,
    //template_parameter_list m_template_parameter_list;
    declaration&& a_declaration
):
    export_keyword_(export_keyword),
    declaration_(std::make_shared<declaration>(std::move(a_declaration)))
{
	update_node_list();
}

template_declaration::template_declaration(const template_declaration& o):
	composite_node(),
    export_keyword_(o.export_keyword_),
    declaration_(o.declaration_)
{
	update_node_list();
}

template_declaration::template_declaration(template_declaration&& o):
    export_keyword_(std::move(o.export_keyword_)),
    declaration_(std::move(o.declaration_))
{
	update_node_list();
}

const template_declaration&
template_declaration::operator=(const template_declaration& o)
{
    export_keyword_ = o.export_keyword_;
    declaration_ = o.declaration_;
	update_node_list();

	return *this;
}

void
template_declaration::update_node_list()
{
	clear();
	add(*declaration_);
}

}}} //namespace socoa::cpp::syntax_nodes
