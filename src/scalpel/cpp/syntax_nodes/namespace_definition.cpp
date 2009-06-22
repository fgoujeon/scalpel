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

#include "namespace_definition.hpp"

#include "declaration_seq.hpp"
#include "common_nodes.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

namespace_definition::namespace_definition
(
	predefined_text_node<str::namespace_>&& o0,
	optional_node<space>&& o1,
	optional_node<identifier>&& o2,
	optional_node<space>&& o3,
	optional_node<leaf_node>&& o3b,
	optional_node<space>&& o3c,
	predefined_text_node<str::opening_brace>&& o4,
	optional_node<space>&& o5,
	optional_node<declaration_seq>&& o6,
	optional_node<space>&& o7,
	predefined_text_node<str::closing_brace>&& o8
):
	impl_
	(
		new type
		(
			o0,
			o1,
			o2,
			o3,
			o3b,
			o3c,
			o4,
			o5,
			o6,
			o7,
			o8
		)
	)
{
	add(*impl_);
}

namespace_definition::namespace_definition(head_node_t&& head, tail_sequence_node_t&& tail):
	impl_(new type(head, tail))
{
	add(*impl_);
}

namespace_definition::namespace_definition(const namespace_definition& o):
	composite_node(),
	impl_(new type(*o.impl_))
{
	add(*impl_);
}

namespace_definition::namespace_definition(namespace_definition&& o):
	impl_(o.impl_)
{
	o.impl_ = 0;
}

namespace_definition::~namespace_definition()
{
	delete impl_;
}

const namespace_definition&
namespace_definition::operator=(const namespace_definition& o)
{
	*impl_ = *o.impl_;
	return *this;
}

const optional_node<identifier>&
namespace_definition::identifier_node() const
{
	return get<2>(*impl_);
}

const optional_node<list_node<declaration>>&
namespace_definition::declaration_seq_node() const
{
	return get<8>(*impl_);
}

}}} //namespace scalpel::cpp::syntax_nodes
