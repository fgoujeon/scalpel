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

#include "using_directive.hpp"

#include "common_nodes.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

using_directive::using_directive
(
	simple_text_node<str::using_>&& o0,
	optional_node<space>&& o1,
	simple_text_node<str::namespace_>&& o2,
	optional_node<space>&& o3,
	optional_node<simple_text_node<str::double_colon>>&& o4,
	optional_node<space>&& o5,
	optional_node<nested_name_specifier>&& o6,
	optional_node<space>&& o7,
	identifier&& o8,
	optional_node<space>&& o9,
	simple_text_node<str::semicolon>&& o10
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
			o6,
			o7,
			o8,
			o9,
			o10
		)
	)
{
}

using_directive::using_directive(head_node_t&& head, tail_sequence_node_t&& tail):
	impl_(new type(head, tail))
{
}

using_directive::using_directive(const using_directive& o):
	composite_node(),
	impl_(new type(*o.impl_))
{
}

using_directive::using_directive(using_directive&& o):
	impl_(std::move(o.impl_))
{
}

const using_directive&
using_directive::operator=(const using_directive& o)
{
	*impl_ = *o.impl_;
	return *this;
}

bool
using_directive::double_colon_node() const
{
	return get<4>(*impl_);
}

const optional_node<nested_name_specifier>&
using_directive::nested_name_specifier_node() const
{
	return get<6>(*impl_);
}

const identifier&
using_directive::identifier_node() const
{
	return get<8>(*impl_);
}

}}} //namespace scalpel::cpp::syntax_nodes

