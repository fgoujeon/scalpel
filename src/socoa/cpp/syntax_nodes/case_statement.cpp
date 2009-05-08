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

#include "case_statement.hpp"

#include "common_nodes.hpp"
#include "statement.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

case_statement::case_statement
(
	boost::optional<space>&& post_case_keyword_space_node,
	conditional_expression&& conditional_expression_node,
	boost::optional<space>&& post_conditional_expression_space_node,
	boost::optional<space>&& post_colon_space_node,
	statement&& statement_node
):
	post_case_keyword_space_(post_case_keyword_space_node),
	conditional_expression_(conditional_expression_node),
	post_conditional_expression_space_(post_conditional_expression_space_node),
	post_colon_space_(post_colon_space_node),
	statement_(new statement(statement_node))
{
	update_node_list();
}

case_statement::case_statement(const case_statement& o):
	composite_node(),
	post_case_keyword_space_(o.post_case_keyword_space_),
	conditional_expression_(o.conditional_expression_),
	post_conditional_expression_space_(o.post_conditional_expression_space_),
	post_colon_space_(o.post_colon_space_),
	statement_(new statement(*o.statement_))
{
	update_node_list();
}

case_statement::case_statement(case_statement&& o):
	composite_node(),
	post_case_keyword_space_(std::move(o.post_case_keyword_space_)),
	conditional_expression_(std::move(o.conditional_expression_)),
	post_conditional_expression_space_(std::move(o.post_conditional_expression_space_)),
	post_colon_space_(std::move(o.post_colon_space_)),
	statement_(std::move(o.statement_))
{
	update_node_list();
}

const case_statement&
case_statement::operator=(const case_statement& o)
{
	post_case_keyword_space_ = o.post_case_keyword_space_;
	conditional_expression_ = o.conditional_expression_;
	post_conditional_expression_space_ = o.post_conditional_expression_space_;
	post_colon_space_ = o.post_colon_space_;
	statement_ = std::move(std::unique_ptr<statement>(new statement(*o.statement_)));

	update_node_list();

	return *this;
}

void
case_statement::update_node_list()
{
	clear();
	add(global_nodes::case_keyword);
	if(post_case_keyword_space_) add(*post_case_keyword_space_);
	add(conditional_expression_);
	add(global_nodes::colon);
	if(post_colon_space_) add(*post_colon_space_);
	add(*statement_);
}

}}} //namespace socoa::cpp::syntax_nodes

