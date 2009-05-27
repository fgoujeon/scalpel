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

#include "using_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

using_declaration::using_declaration
(
	simple_text_node<str::using_>&& o0,
	optional_node<space>&& o1,
	optional_node<simple_text_node<str::typename_>>&& o2,
	optional_node<space>&& o3,
	optional_node<simple_text_node<str::double_colon>>&& o4,
	optional_node<space>&& o5,
	optional_node<nested_name_specifier>&& o6,
	optional_node<space>&& o7,
	unqualified_id&& o8,
	optional_node<space>&& o9,
	simple_text_node<str::semicolon>&& o10
):
	impl_(o0, o1, o2, o3, o4, o5, o6, o7, o8, o9, o10)
{
	add(impl_);
}

using_declaration::using_declaration
(
	head_node_t&& head,
	tail_sequence_node_t&& tail
):
	impl_(head, tail)
{
	add(impl_);
}

using_declaration::using_declaration(const using_declaration& o):
	impl_(o.impl_)
{
	add(impl_);
}

using_declaration::using_declaration(using_declaration&& o):
	impl_(std::move(o.impl_))
{
	add(impl_);
}

const using_declaration&
using_declaration::operator=(const using_declaration& o)
{
	impl_ = o.impl_;
	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes
