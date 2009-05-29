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

#include "qualified_identifier.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

qualified_identifier::qualified_identifier
(
	simple_text_node<str::double_colon>&& o0,
	optional_node<space>&& o1,
	identifier&& o2
):
	impl_(o0, o1, o2)
{
	add(impl_);
}

qualified_identifier::qualified_identifier
(
	head_node_t&& head,
	tail_sequence_node_t&& tail
):
	impl_(head, tail)
{
	add(impl_);
}

qualified_identifier::qualified_identifier(const qualified_identifier& o):
	composite_node(),
    impl_(o.impl_)
{
	add(impl_);
}

qualified_identifier::qualified_identifier(qualified_identifier&& o):
	composite_node(),
    impl_(std::move(o.impl_))
{
	add(impl_);
}

const qualified_identifier&
qualified_identifier::operator=(const qualified_identifier& o)
{
	impl_ = o.impl_;
	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes
