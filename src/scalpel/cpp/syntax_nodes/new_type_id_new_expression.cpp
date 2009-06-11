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

#include "new_type_id_new_expression.hpp"

#include "new_initializer.hpp"
#include "common_nodes.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

new_type_id_new_expression::new_type_id_new_expression
(
	bool leading_double_colon,
	optional_node<space>&& post_double_colon_space_node,
	optional_node<space>&& post_new_keyword_space_node,
	optional_node<round_bracketed_expression>&& round_bracketed_expression_node,
	optional_node<space>&& post_round_bracketed_expression_space_node,
	new_type_id&& new_type_id_node,
	optional_node<space>&& pre_new_initializer_space_node,
	optional_node<new_initializer>&& new_initializer_node
):
	leading_double_colon_(leading_double_colon),
	post_double_colon_space_(post_double_colon_space_node),
	post_new_keyword_space_(post_new_keyword_space_node),
	round_bracketed_expression_(round_bracketed_expression_node),
	post_round_bracketed_expression_space_(post_round_bracketed_expression_space_node),
	new_type_id_(new_type_id_node),
	pre_new_initializer_space_(pre_new_initializer_space_node)
{
	if(new_initializer_node)
		new_initializer_ = std::move(std::unique_ptr<new_initializer>(new new_initializer(std::move(*new_initializer_node))));
	else
		new_initializer_ = 0;
	update_node_list();
}

new_type_id_new_expression::new_type_id_new_expression(const new_type_id_new_expression& o):
	composite_node(),
	leading_double_colon_(o.leading_double_colon_),
	post_double_colon_space_(o.post_double_colon_space_),
	post_new_keyword_space_(o.post_new_keyword_space_),
	round_bracketed_expression_(o.round_bracketed_expression_),
	post_round_bracketed_expression_space_(o.post_round_bracketed_expression_space_),
	new_type_id_(o.new_type_id_),
	pre_new_initializer_space_(o.pre_new_initializer_space_)
{
	if(o.new_initializer_)
		new_initializer_ = std::move(std::unique_ptr<new_initializer>(new new_initializer(std::move(*o.new_initializer_))));
	else
		new_initializer_ = 0;
	update_node_list();
}

new_type_id_new_expression::new_type_id_new_expression(new_type_id_new_expression&& o):
	composite_node(),
	leading_double_colon_(o.leading_double_colon_),
	post_double_colon_space_(std::move(o.post_double_colon_space_)),
	post_new_keyword_space_(std::move(o.post_new_keyword_space_)),
	round_bracketed_expression_(std::move(o.round_bracketed_expression_)),
	post_round_bracketed_expression_space_(std::move(o.post_round_bracketed_expression_space_)),
	new_type_id_(std::move(o.new_type_id_)),
	pre_new_initializer_space_(std::move(o.pre_new_initializer_space_)),
	new_initializer_(std::move(o.new_initializer_))
{
	update_node_list();
}

const new_type_id_new_expression&
new_type_id_new_expression::operator=(const new_type_id_new_expression& o)
{
	leading_double_colon_ = o.leading_double_colon_;
	post_double_colon_space_ = o.post_double_colon_space_;
	post_new_keyword_space_ = o.post_new_keyword_space_;
	round_bracketed_expression_ = o.round_bracketed_expression_;
	post_round_bracketed_expression_space_ = o.post_round_bracketed_expression_space_;
	new_type_id_ = o.new_type_id_;
	pre_new_initializer_space_ = o.pre_new_initializer_space_;
	if(o.new_initializer_)
		new_initializer_ = std::move(std::unique_ptr<new_initializer>(new new_initializer(std::move(*o.new_initializer_))));
	else
		new_initializer_ = 0;

	update_node_list();

	return *this;
}

void
new_type_id_new_expression::update_node_list()
{
	clear();
	if(leading_double_colon_) add(common_nodes::double_colon);
	if(post_double_colon_space_) add(*post_double_colon_space_);
	add(common_nodes::new_keyword);
	if(post_new_keyword_space_) add(*post_new_keyword_space_);
	if(round_bracketed_expression_) add(*round_bracketed_expression_);
	if(post_round_bracketed_expression_space_) add(*post_round_bracketed_expression_space_);
	add(new_type_id_);
	if(pre_new_initializer_space_) add(*pre_new_initializer_space_);
	if(new_initializer_) add(*new_initializer_);
}

}}} //namespace scalpel::cpp::syntax_nodes

