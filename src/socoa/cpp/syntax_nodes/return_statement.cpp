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

#include "return_statement.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

return_statement::return_statement
(
	boost::optional<space>&& post_return_space_node,
	boost::optional<expression>&& expression_node,
	boost::optional<space>&& post_expression_space_node
):
	post_return_space_(post_return_space_node),
	expression_(expression_node),
	post_expression_space_(post_expression_space_node)
{
	update_node_list();
}

return_statement::return_statement(const return_statement& o):
	composite_node(),
	post_return_space_(o.post_return_space_),
	expression_(o.expression_),
	post_expression_space_(o.post_expression_space_)
{
	update_node_list();
}

return_statement::return_statement(return_statement&& o):
	composite_node(),
	post_return_space_(std::move(o.post_return_space_)),
	expression_(std::move(o.expression_)),
	post_expression_space_(std::move(o.post_expression_space_))
{
	update_node_list();
}

const return_statement&
return_statement::operator=(const return_statement& o)
{
	post_return_space_ = o.post_return_space_;
	expression_ = o.expression_;
	post_expression_space_ = o.post_expression_space_;

	update_node_list();

	return *this;
}

void
return_statement::update_node_list()
{
	clear();
	add(return_keyword);
	if(post_return_space_) add(*post_return_space_);
	if(expression_) add(*expression_);
	if(post_expression_space_) add(*post_expression_space_);
	add(semicolon);
}

}}} //namespace socoa::cpp::syntax_nodes

