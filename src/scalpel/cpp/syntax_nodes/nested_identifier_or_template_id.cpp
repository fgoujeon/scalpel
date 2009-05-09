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

#include "nested_identifier_or_template_id.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

nested_identifier_or_template_id::nested_identifier_or_template_id
(
    bool leading_double_colon,
    boost::optional<nested_name_specifier>&& a_nested_name_specifier,
    identifier_or_template_id&& an_identifier_or_template_id
):
    leading_double_colon_(leading_double_colon),
    nested_name_specifier_(a_nested_name_specifier),
    identifier_or_template_id_(std::move(an_identifier_or_template_id))
{
	update_node_list();
}

nested_identifier_or_template_id::nested_identifier_or_template_id(const nested_identifier_or_template_id& o):
	composite_node(),
    leading_double_colon_(o.leading_double_colon_),
    nested_name_specifier_(o.nested_name_specifier_),
    identifier_or_template_id_(o.identifier_or_template_id_)
{
	update_node_list();
}

nested_identifier_or_template_id::nested_identifier_or_template_id(nested_identifier_or_template_id&& o):
    leading_double_colon_(std::move(o.leading_double_colon_)),
    nested_name_specifier_(std::move(o.nested_name_specifier_)),
    identifier_or_template_id_(std::move(o.identifier_or_template_id_))
{
	update_node_list();
}

const nested_identifier_or_template_id&
nested_identifier_or_template_id::operator=(const nested_identifier_or_template_id& o)
{
    leading_double_colon_ = o.leading_double_colon_;
    nested_name_specifier_ = o.nested_name_specifier_;
    identifier_or_template_id_ = o.identifier_or_template_id_;
	update_node_list();

	return *this;
}

void
nested_identifier_or_template_id::update_node_list()
{
	clear();
	if(nested_name_specifier_) add(*nested_name_specifier_);
	add(identifier_or_template_id_);
}

}}} //namespace scalpel::cpp::syntax_nodes
