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

#include "postfix_expression.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

postfix_expression::postfix_expression
(
	boost::optional<primary_expression>&& primary_expression_node
):
	primary_expression_(primary_expression_node)
{
	update_node_list();
}

postfix_expression::postfix_expression(const postfix_expression& o):
	composite_node(),
	primary_expression_(o.primary_expression_)
{
	update_node_list();
}

postfix_expression::postfix_expression(postfix_expression&& o):
	composite_node(),
	primary_expression_(std::move(o.primary_expression_))
{
	update_node_list();
}

const postfix_expression&
postfix_expression::operator=(const postfix_expression& o)
{
	primary_expression_ = o.primary_expression_;

	update_node_list();

	return *this;
}

void
postfix_expression::update_node_list()
{
	clear();
	if(primary_expression_) add(*primary_expression_);
}

}}} //namespace socoa::cpp::syntax_tree

