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

#include "template_type_parameter.hpp"

#include "template_parameter_list.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

template_type_parameter::template_type_parameter
(
	predefined_text_node<str::template_>&& o0,
	optional_node<space>&& o1,
	predefined_text_node<str::left_angle_bracket>&& o2,
	optional_node<space>&& o3,
	template_parameter_list&& o4,
	optional_node<space>&& o5,
	predefined_text_node<str::right_angle_bracket>&& o6,
	optional_node<space>&& o7,
	predefined_text_node<str::class_>&& o8,
	optional_node<space>&& o9,
	optional_node<identifier>&& o10,
	optional_node<space>&& o11,
	optional_node<predefined_text_node<str::equal>>&& o12,
	optional_node<space>&& o13,
	optional_node<id_expression>&& o14
):
	impl_
	(
		new type(o0, o1, o2, o3, o4, o5, o6, o7, o8, o9, o10, o11, o12, o13, o14)
	)
{
	add(*impl_);
}

template_type_parameter::template_type_parameter
(
	head_node_t&& head,
	tail_sequence_node_t&& tail
):
	impl_(new type(head, tail))
{
	add(*impl_);
}

template_type_parameter::template_type_parameter(const template_type_parameter& o):
	composite_node(),
	impl_(new type(*o.impl_))
{
	add(*impl_);
}

template_type_parameter::template_type_parameter(template_type_parameter&& o):
	composite_node(),
	impl_(std::move(o.impl_))
{
	add(*impl_);
}

template_type_parameter::~template_type_parameter()
{
}

const template_type_parameter&
template_type_parameter::operator=(const template_type_parameter& o)
{
	*impl_ = *o.impl_;
	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes

