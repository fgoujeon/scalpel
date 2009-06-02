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

#include "nested_name_specifier.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

nested_name_specifier::nested_name_specifier
(
	identifier_or_template_id&& o0,
	optional_node<space>&& o1,
	simple_text_node<str::double_colon>&& o2,
	optional_node<space>&& o3,
	optional_node<nested_name_specifier_last_part_seq>&& o4
):
	impl_(o0, o1, o2, o3, o4)
{
	add(impl_);
}

nested_name_specifier::nested_name_specifier
(
	head_node_t&& head,
	tail_sequence_node_t&& tail
):
	impl_(head, tail)
{
	add(impl_);
}

nested_name_specifier::nested_name_specifier(const nested_name_specifier& o):
	composite_node(),
	impl_(o.impl_)
{
	add(impl_);
}

nested_name_specifier::nested_name_specifier(nested_name_specifier&& o):
	composite_node(),
	impl_(std::move(o.impl_))
{
	add(impl_);
}

const nested_name_specifier&
nested_name_specifier::operator=(const nested_name_specifier& o)
{
	impl_ = o.impl_;
	return *this;
}



nested_name_specifier_last_part::nested_name_specifier_last_part
(
	optional_node<simple_text_node<str::template_>>&& o0,
	optional_node<space>&& o1,
	identifier_or_template_id&& o2,
	optional_node<space>&& o3,
	simple_text_node<str::double_colon>&& o4
):
	impl_(o0, o1, o2, o3, o4)
{
	add(impl_);
}

nested_name_specifier_last_part::nested_name_specifier_last_part
(
	head_node_t&& head,
	tail_sequence_node_t&& tail
):
	impl_(head, tail)
{
	add(impl_);
}

nested_name_specifier_last_part::nested_name_specifier_last_part(const nested_name_specifier_last_part& o):
	composite_node(),
	impl_(o.impl_)
{
	add(impl_);
}

nested_name_specifier_last_part::nested_name_specifier_last_part(nested_name_specifier_last_part&& o):
	composite_node(),
	impl_(std::move(o.impl_))
{
	add(impl_);
}

const nested_name_specifier_last_part&
nested_name_specifier_last_part::operator=(const nested_name_specifier_last_part& o)
{
	impl_ = o.impl_;
	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes
