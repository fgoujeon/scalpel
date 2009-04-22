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

#include "simple_template_type_specifier.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

simple_template_type_specifier::simple_template_type_specifier
(
    bool leading_double_colon,
    nested_name_specifier&& a_nested_name_specifier,
    template_id&& a_template_id
):
    leading_double_colon_(leading_double_colon),
    nested_name_specifier_(std::move(a_nested_name_specifier)),
    template_id_(std::move(a_template_id))
{
	update_node_list();
}

simple_template_type_specifier::simple_template_type_specifier(const simple_template_type_specifier& o):
	composite_node(),
    leading_double_colon_(o.leading_double_colon_),
    nested_name_specifier_(o.nested_name_specifier_),
    template_id_(o.template_id_)
{
	update_node_list();
}

simple_template_type_specifier::simple_template_type_specifier(simple_template_type_specifier&& o):
    leading_double_colon_(std::move(o.leading_double_colon_)),
    nested_name_specifier_(std::move(o.nested_name_specifier_)),
    template_id_(std::move(o.template_id_))
{
	update_node_list();
}

const simple_template_type_specifier&
simple_template_type_specifier::operator=(const simple_template_type_specifier& o)
{
    leading_double_colon_ = o.leading_double_colon_;
    nested_name_specifier_ = o.nested_name_specifier_;
    template_id_ = o.template_id_;
	update_node_list();

	return *this;
}

void
simple_template_type_specifier::update_node_list()
{
	clear();
	add(nested_name_specifier_);
	add(template_id_);
}

}}} //namespace socoa::cpp::syntax_nodes
