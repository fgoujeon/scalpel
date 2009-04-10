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

#include "nested_name_specifier.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

nested_name_specifier::nested_name_specifier
(
	identifier_or_template_id&& an_identifier_or_template_id,
	second_parts_t&& parts
):
	identifier_or_template_id_(std::move(an_identifier_or_template_id)),
	parts_(std::move(parts))
{
}

nested_name_specifier::nested_name_specifier(nested_name_specifier&& o):
	identifier_or_template_id_(std::move(o.identifier_or_template_id_)),
	parts_(std::move(o.parts_))
{
}


nested_name_specifier::second_part::second_part
(
	bool template_keyword,
	identifier_or_template_id&& an_identifier_or_template_id
):
	template_keyword_(template_keyword),
	identifier_or_template_id_(an_identifier_or_template_id)
{
	add(identifier_or_template_id_);
}

nested_name_specifier::second_part::second_part(second_part&& o):
	template_keyword_(std::move(o.template_keyword_)),
	identifier_or_template_id_(std::move(o.identifier_or_template_id_))
{
}

}}} //namespace socoa::cpp::syntax_tree
