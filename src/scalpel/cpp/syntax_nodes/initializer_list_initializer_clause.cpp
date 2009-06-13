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

#include "initializer_list_initializer_clause.hpp"

#include "initializer_list.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

initializer_list_initializer_clause::initializer_list_initializer_clause
(
	simple_text_node<str::opening_brace>&& o0,
	optional_node<space>&& o1,
	optional_node<initializer_list>&& o2,
	optional_node<space>&& o3,
	optional_node<simple_text_node<str::comma>>&& o4,
	optional_node<space>&& o5,
	simple_text_node<str::closing_brace>&& o6
):
	impl_(new type(o0, o1, o2, o3, o4, o5, o6))
{
	add(*impl_);
}

initializer_list_initializer_clause::initializer_list_initializer_clause
(
	head_node_t&& head,
	tail_sequence_node_t&& tail
):
	impl_(new type(head, tail))
{
	add(*impl_);
}

initializer_list_initializer_clause::initializer_list_initializer_clause(const initializer_list_initializer_clause& o):
	composite_node(),
	impl_(new type(*o.impl_))
{
	add(*impl_);
}

initializer_list_initializer_clause::initializer_list_initializer_clause(initializer_list_initializer_clause&& o):
	composite_node(),
	impl_(std::move(o.impl_))
{
	add(*impl_);
}

initializer_list_initializer_clause::~initializer_list_initializer_clause()
{
}

const initializer_list_initializer_clause&
initializer_list_initializer_clause::operator=(const initializer_list_initializer_clause& o)
{
	*impl_ = *o.impl_;
	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes

