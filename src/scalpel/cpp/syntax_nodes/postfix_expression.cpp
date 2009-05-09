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
	first_part&& first_part_node,
	boost::optional<space>&& space_node,
	boost::optional<last_part_seq>&& last_part_seq_node
):
	first_part_(first_part_node),
	space_(space_node),
	last_part_seq_(last_part_seq_node)
{
	update_node_list();
}

postfix_expression::postfix_expression(const postfix_expression& o):
	composite_node(),
	first_part_(o.first_part_),
	space_(o.space_),
	last_part_seq_(o.last_part_seq_)
{
	update_node_list();
}

postfix_expression::postfix_expression(postfix_expression&& o):
	composite_node(),
	first_part_(std::move(o.first_part_)),
	space_(std::move(o.space_)),
	last_part_seq_(std::move(o.last_part_seq_))
{
	update_node_list();
}

const postfix_expression&
postfix_expression::operator=(const postfix_expression& o)
{
	first_part_ = o.first_part_;
	space_ = o.space_;
	last_part_seq_ = o.last_part_seq_;

	update_node_list();

	return *this;
}

void
postfix_expression::update_node_list()
{
	clear();
	add(first_part_);
	if(space_) add(*space_);
	if(last_part_seq_) add(*last_part_seq_);
}

}}} //namespace scalpel::cpp::syntax_nodes

