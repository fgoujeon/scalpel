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

#include "template_id.hpp"

#include "template_argument_list.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

template_id::template_id
(
	identifier&& o0,
	optional_node<space>&& o1,
	predefined_text_node<str::left_angle_bracket>&& o2,
	optional_node<space>&& o3,
	optional_node<template_argument_list>&& o4,
	optional_node<space>&& o5,
	predefined_text_node<str::right_angle_bracket>&& o6
):
	impl_
	(
		new type
		(
			o0,
			o1,
			o2,
			o3,
			o4,
			o5,
			o6
		)
	)
{
	add(*impl_);
}

template_id::template_id
(
	head_node_t&& head,
	tail_sequence_node_t&& tail
):
	impl_
	(
		new type
		(
			head,
			tail
		)
	)
{
	add(*impl_);
}

template_id::template_id(const template_id& o):
	composite_node(),
	impl_(new type(*o.impl_))
{
	add(*impl_);
}

template_id::template_id(template_id&& o):
	impl_(std::move(o.impl_))
{
	add(*impl_);
}

template_id::~template_id()
{
}

const template_id&
template_id::operator=(const template_id& o)
{
	*impl_ = *o.impl_;
	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes
