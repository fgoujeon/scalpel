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

#include "postfix_expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

postfix_expression::postfix_expression
(
	first_part&& o0,
	optional_node<space>&& o1,
	optional_node<last_part_seq>&& o2
):
	impl_(o0, o1, o2)
{
	add(impl_);
}

postfix_expression::postfix_expression
(
	head_node_t&& head,
	tail_sequence_node_t&& tail
):
	impl_(head, tail)
{
	add(impl_);
}

postfix_expression::postfix_expression(const postfix_expression& o):
	composite_node(),
	impl_(o.impl_)
{
	add(impl_);
}

postfix_expression::postfix_expression(postfix_expression&& o):
	composite_node(),
	impl_(o.impl_)
{
	add(impl_);
}

const postfix_expression&
postfix_expression::operator=(const postfix_expression& o)
{
	impl_ = o.impl_;
	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes

