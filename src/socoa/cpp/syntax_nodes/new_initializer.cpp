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

#include "new_initializer.hpp"
#include "expression_list.hpp"

#include "common_nodes.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

new_initializer::new_initializer
(
	boost::optional<space>&& post_opening_bracket_space_node,
	boost::optional<expression_list>&& expression_list_node,
	boost::optional<space>&& post_expression_list_space_node
):
	post_opening_bracket_space_(post_opening_bracket_space_node),
	post_expression_list_space_(post_expression_list_space_node)
{
	if(expression_list_node)
		expression_list_ = new expression_list(*expression_list_node);
	else
		expression_list_ = 0;
	update_node_list();
}

new_initializer::new_initializer(const new_initializer& o):
	composite_node(),
	post_opening_bracket_space_(o.post_opening_bracket_space_),
	post_expression_list_space_(o.post_expression_list_space_)
{
	if(o.expression_list_)
		expression_list_ = new expression_list(*o.expression_list_);
	else
		expression_list_ = 0;
	update_node_list();
}

new_initializer::new_initializer(new_initializer&& o):
	composite_node(),
	post_opening_bracket_space_(std::move(o.post_opening_bracket_space_)),
	expression_list_(std::move(o.expression_list_)),
	post_expression_list_space_(std::move(o.post_expression_list_space_))
{
	o.expression_list_ = 0;
	update_node_list();
}

new_initializer::~new_initializer()
{
	delete expression_list_;
}

const new_initializer&
new_initializer::operator=(const new_initializer& o)
{
	post_opening_bracket_space_ = o.post_opening_bracket_space_;
	delete expression_list_;
	if(o.expression_list_)
		expression_list_ = new expression_list(*o.expression_list_);
	else
		expression_list_ = 0;
	post_expression_list_space_ = o.post_expression_list_space_;

	update_node_list();

	return *this;
}

void
new_initializer::update_node_list()
{
	clear();
	add(opening_bracket);
	if(post_opening_bracket_space_) add(*post_opening_bracket_space_);
	if(expression_list_) add(*expression_list_);
	if(post_expression_list_space_) add(*post_expression_list_space_);
	add(closing_bracket);
}

}}} //namespace socoa::cpp::syntax_nodes

