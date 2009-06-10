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

#include "simple_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

simple_declaration::simple_declaration
(
	optional_node<decl_specifier_seq>&& o0,
	optional_node<space>&& o1,
	optional_node<init_declarator_list>&& o2,
	optional_node<space>&& o3,
	simple_text_node<str::semicolon>&& o4
):
	impl_(o0, o1, o2, o3, o4)
{
	add(impl_);
}

simple_declaration::simple_declaration
(
	head_node_t&& head,
	tail_sequence_node_t&& tail
):
	impl_(head, tail)
{
	add(impl_);
}

simple_declaration::simple_declaration(const simple_declaration& o):
	composite_node(),
	impl_(o.impl_)
{
	add(impl_);
}

simple_declaration::simple_declaration(simple_declaration&& o):
	composite_node(),
	impl_(std::move(o.impl_))
{
	add(impl_);
}

const simple_declaration&
simple_declaration::operator=(const simple_declaration& o)
{
	impl_ = o.impl_;
	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes
