/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "assignment_expression.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

assignment_expression::assignment_expression
(
	boost::optional<first_part_seq>&& first_part_seq_node,
	boost::optional<space>&& space_node,
	conditional_or_throw_expression&& conditional_or_throw_expression_node
):
	first_part_seq_(first_part_seq_node),
	space_(space_node),
	conditional_or_throw_expression_(conditional_or_throw_expression_node)
{
	update_node_list();
}

assignment_expression::assignment_expression(const assignment_expression& o):
	composite_node(),
	first_part_seq_(o.first_part_seq_),
	space_(o.space_),
	conditional_or_throw_expression_(o.conditional_or_throw_expression_)
{
	update_node_list();
}

assignment_expression::assignment_expression(assignment_expression&& o):
	composite_node(),
	first_part_seq_(std::move(o.first_part_seq_)),
	space_(std::move(o.space_)),
	conditional_or_throw_expression_(std::move(o.conditional_or_throw_expression_))
{
	update_node_list();
}

const assignment_expression&
assignment_expression::operator=(const assignment_expression& o)
{
	first_part_seq_ = o.first_part_seq_;
	space_ = o.space_;
	conditional_or_throw_expression_ = o.conditional_or_throw_expression_;

	update_node_list();

	return *this;
}

void
assignment_expression::update_node_list()
{
	clear();
	if(first_part_seq_) add(*first_part_seq_);
	if(space_) add(*space_);
	add(conditional_or_throw_expression_);
}


assignment_expression::first_part::first_part
(
	logical_or_expression&& logical_or_expression_node,
	boost::optional<space>&& space_node,
	assignment_operator&& assignment_operator_node
):
	logical_or_expression_(logical_or_expression_node),
	space_(space_node),
	assignment_operator_(assignment_operator_node)
{
	update_node_list();
}

assignment_expression::first_part::first_part(const assignment_expression::first_part::first_part& o):
	composite_node(),
	logical_or_expression_(o.logical_or_expression_),
	space_(o.space_),
	assignment_operator_(o.assignment_operator_)
{
	update_node_list();
}

assignment_expression::first_part::first_part(assignment_expression::first_part::first_part&& o):
	composite_node(),
	logical_or_expression_(std::move(o.logical_or_expression_)),
	space_(std::move(o.space_)),
	assignment_operator_(std::move(o.assignment_operator_))
{
	update_node_list();
}

const assignment_expression::first_part::first_part&
assignment_expression::first_part::operator=(const assignment_expression::first_part::first_part& o)
{
	logical_or_expression_ = o.logical_or_expression_;
	space_ = o.space_;
	assignment_operator_ = o.assignment_operator_;

	update_node_list();

	return *this;
}

void
assignment_expression::first_part::update_node_list()
{
	clear();

	add(logical_or_expression_);
	if(space_) add(*space_);
	add(assignment_operator_);
}

}}} //namespace socoa::cpp::syntax_nodes
