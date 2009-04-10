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

namespace socoa { namespace cpp { namespace syntax_tree
{

assignment_expression::assignment_expression
(
    assignment_operator&& an_assignment_operator
):
    assignment_operator_(std::move(an_assignment_operator))
{
	update_node_list();
}

assignment_expression::assignment_expression(const assignment_expression& o):
	composite_node(),
	assignment_operator_(o.assignment_operator_)
{
	update_node_list();
}

assignment_expression::assignment_expression(assignment_expression&& o):
	assignment_operator_(std::move(o.assignment_operator_))
{
	update_node_list();
}

const assignment_expression&
assignment_expression::operator=(const assignment_expression& o)
{
	assignment_operator_ = o.assignment_operator_;
	update_node_list();

	return *this;
}

void
assignment_expression::update_node_list()
{
	clear();
	add(assignment_operator_);
}

}}} //namespace socoa::cpp::syntax_tree
