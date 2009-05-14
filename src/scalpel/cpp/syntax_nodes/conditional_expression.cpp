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

#include "conditional_expression.hpp"

#include "expressions.hpp"
#include "common_nodes.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

conditional_expression::conditional_expression
(
	logical_or_expression&& logical_or_expression_node,
	boost::optional<space>&& pre_question_mark_space_node,
	boost::optional<space>&& post_question_mark_space_node,
	boost::optional<expression>&& expression_node,
	boost::optional<space>&& post_expression_space_node,
	boost::optional<space>&& post_colon_space_node,
	boost::optional<assignment_expression>&& assignment_expression_node
):
	logical_or_expression_(new logical_or_expression(logical_or_expression_node)),
	pre_question_mark_space_(pre_question_mark_space_node),
	post_question_mark_space_(post_question_mark_space_node),
	post_expression_space_(post_expression_space_node),
	post_colon_space_(post_colon_space_node)
{
	if(expression_node)
		expression_ = std::move(std::unique_ptr<expression>(new expression(*expression_node)));
	if(assignment_expression_node)
		assignment_expression_ = std::move(std::unique_ptr<assignment_expression>(new assignment_expression(*assignment_expression_node)));
	update_node_list();
}

conditional_expression::conditional_expression(const conditional_expression& o):
	composite_node(),
	logical_or_expression_(new logical_or_expression(*o.logical_or_expression_)),
	pre_question_mark_space_(o.pre_question_mark_space_),
	post_question_mark_space_(o.post_question_mark_space_),
	post_expression_space_(o.post_expression_space_),
	post_colon_space_(o.post_colon_space_)
{
	if(o.expression_)
		expression_ = std::move(std::unique_ptr<expression>(new expression(*o.expression_)));
	if(o.assignment_expression_)
		assignment_expression_ = std::move(std::unique_ptr<assignment_expression>(new assignment_expression(*o.assignment_expression_)));
	update_node_list();
}

conditional_expression::conditional_expression(conditional_expression&& o):
	composite_node(),
	logical_or_expression_(o.logical_or_expression_),
	pre_question_mark_space_(std::move(o.pre_question_mark_space_)),
	post_question_mark_space_(std::move(o.post_question_mark_space_)),
	expression_(std::move(o.expression_)),
	post_expression_space_(std::move(o.post_expression_space_)),
	post_colon_space_(std::move(o.post_colon_space_)),
	assignment_expression_(std::move(o.assignment_expression_))
{
	o.logical_or_expression_ = 0;
	update_node_list();
}

conditional_expression::~conditional_expression()
{
	delete logical_or_expression_;
}

const conditional_expression&
conditional_expression::operator=(const conditional_expression& o)
{
	conditional_expression copy(o);
	std::swap(copy, *this);
	return *this;
}

void
conditional_expression::update_node_list()
{
	clear();
	add(*logical_or_expression_);
	if(expression_)
	{
		if(pre_question_mark_space_) add(*pre_question_mark_space_);
		add(global_nodes::question_mark);
		if(post_question_mark_space_) add(*post_question_mark_space_);
		add(*expression_);
		if(post_expression_space_) add(*post_expression_space_);
		add(global_nodes::colon);
		if(post_colon_space_) add(*post_colon_space_);
		add(*assignment_expression_);
	}
}

}}} //namespace scalpel::cpp::syntax_nodes

