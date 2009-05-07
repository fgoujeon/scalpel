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

#include "arrow_id_expression.hpp"

#include "common_nodes.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

arrow_id_expression::arrow_id_expression
(
	boost::optional<space>&& post_arrow_space_node,
	bool template_keyword,
	boost::optional<space>&& post_template_keyword_space_node,
	id_expression&& id_expression_node
):
	post_arrow_space_(post_arrow_space_node),
	template_keyword_(template_keyword),
	post_template_keyword_space_(post_template_keyword_space_node),
	id_expression_(id_expression_node)
{
	update_node_list();
}

arrow_id_expression::arrow_id_expression(const arrow_id_expression& o):
	composite_node(),
	post_arrow_space_(o.post_arrow_space_),
	template_keyword_(o.template_keyword_),
	post_template_keyword_space_(o.post_template_keyword_space_),
	id_expression_(o.id_expression_)
{
	update_node_list();
}

arrow_id_expression::arrow_id_expression(arrow_id_expression&& o):
	composite_node(),
	post_arrow_space_(std::move(o.post_arrow_space_)),
	template_keyword_(o.template_keyword_),
	post_template_keyword_space_(std::move(o.post_template_keyword_space_)),
	id_expression_(std::move(o.id_expression_))
{
	update_node_list();
}

const arrow_id_expression&
arrow_id_expression::operator=(const arrow_id_expression& o)
{
	post_arrow_space_ = o.post_arrow_space_;
	template_keyword_ = o.template_keyword_;
	post_template_keyword_space_ = o.post_template_keyword_space_;
	id_expression_ = o.id_expression_;

	update_node_list();

	return *this;
}

void
arrow_id_expression::update_node_list()
{
	clear();
	add(arrow);
	if(post_arrow_space_) add(*post_arrow_space_);
	if(template_keyword_) add(template_keyword);
	if(post_template_keyword_space_) add(*post_template_keyword_space_);
	add(id_expression_);
}

}}} //namespace socoa::cpp::syntax_nodes

