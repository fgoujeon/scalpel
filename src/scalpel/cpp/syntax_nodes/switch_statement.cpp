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

#include "switch_statement.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

switch_statement::switch_statement
(
	simple_text_node<str::switch_>&& o0,
	optional_node<space>&& o1,
	simple_text_node<str::opening_round_bracket>&& o2,
	optional_node<space>&& o3,
	condition&& o4,
	optional_node<space>&& o5,
	simple_text_node<str::closing_round_bracket>&& o6,
	optional_node<space>&& o7,
	statement&& o8
):
	impl_(o0, o1, o2, o3, o4, o5, o6, o7, o8)
{
	add(impl_);
}

switch_statement::switch_statement
(
	head_node_t&& head,
	tail_sequence_node_t&& tail
):
	impl_(head, tail)
{
	add(impl_);
}

switch_statement::switch_statement(const switch_statement& o):
	composite_node(),
	impl_(o.impl_)
{
	add(impl_);
}

switch_statement::switch_statement(switch_statement&& o):
	composite_node(),
	impl_(o.impl_)
{
	add(impl_);
}

const switch_statement&
switch_statement::operator=(const switch_statement& o)
{
	impl_ = o.impl_;
	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes

