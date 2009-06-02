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

#include "translation_unit.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

translation_unit::translation_unit
(
	optional_node<space>&& o0,
	optional_node<declaration_seq>&& o1,
	optional_node<space>&& o2
):
	impl_(o0, o1, o2)
{
	add(impl_);
}

translation_unit::translation_unit
(
	head_node_t&& head,
	tail_sequence_node_t&& tail
):
	impl_(head, tail)
{
	add(impl_);
}

translation_unit::translation_unit(const translation_unit& o):
	composite_node(),
	impl_(o.impl_)
{
	add(impl_);
}

translation_unit::translation_unit(translation_unit&& o):
	composite_node(),
	impl_(std::move(o.impl_))
{
	add(impl_);
}

const translation_unit&
translation_unit::operator=(const translation_unit& o)
{
	impl_ = o.impl_;
	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes

