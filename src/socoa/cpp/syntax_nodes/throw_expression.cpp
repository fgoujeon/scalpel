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

#include "throw_expression.hpp"

#include "assignment_expression.hpp"
#include "common_nodes.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

throw_expression::throw_expression
(
	boost::optional<space>&& pre_assignment_expression_space_node,
	boost::optional<assignment_expression>&& assignment_expression_node
):
	pre_assignment_expression_space_(pre_assignment_expression_space_node)
{
	if(assignment_expression_node)
		assignment_expression_ = std::move(std::unique_ptr<assignment_expression>(new assignment_expression(*assignment_expression_node)));

	update_node_list();
}

throw_expression::throw_expression(const throw_expression& o):
	composite_node(),
	pre_assignment_expression_space_(o.pre_assignment_expression_space_)
{
	if(o.assignment_expression_)
		assignment_expression_ = std::move(std::unique_ptr<assignment_expression>(new assignment_expression(*o.assignment_expression_)));

	update_node_list();
}

throw_expression::throw_expression(throw_expression&& o):
	composite_node(),
	pre_assignment_expression_space_(std::move(o.pre_assignment_expression_space_)),
	assignment_expression_(std::move(o.assignment_expression_))
{
	update_node_list();
}

const throw_expression&
throw_expression::operator=(const throw_expression& o)
{
	pre_assignment_expression_space_ = o.pre_assignment_expression_space_;
	if(o.assignment_expression_)
		assignment_expression_ = std::move(std::unique_ptr<assignment_expression>(new assignment_expression(*o.assignment_expression_)));

	update_node_list();

	return *this;
}

void
throw_expression::update_node_list()
{
	clear();
	add(global_nodes::throw_keyword);
	if(pre_assignment_expression_space_) add(*pre_assignment_expression_space_);
	if(assignment_expression_) add(*assignment_expression_);
}

}}} //namespace socoa::cpp::syntax_nodes

