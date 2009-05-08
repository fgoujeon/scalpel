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

#include "for_statement.hpp"

#include "statement.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

for_statement::for_statement
(
	boost::optional<space>&& post_for_keyword_space_node,
	boost::optional<space>&& post_opening_bracket_space_node,
	boost::optional<for_init_statement>&& for_init_statement_node,
	boost::optional<space>&& post_for_init_statement_space_node,
	boost::optional<condition>&& condition_node,
	boost::optional<space>&& post_condition_space_node,
	boost::optional<space>&& post_semicolon_space_node,
	boost::optional<expression>&& expression_node,
	boost::optional<space>&& post_expression_space_node,
	boost::optional<space>&& post_closing_bracket_space_node,
	statement&& statement_node
):
	post_for_keyword_space_(post_for_keyword_space_node),
	post_opening_bracket_space_(post_opening_bracket_space_node),
	for_init_statement_(for_init_statement_node),
	post_for_init_statement_space_(post_for_init_statement_space_node),
	condition_(condition_node),
	post_condition_space_(post_condition_space_node),
	post_semicolon_space_(post_semicolon_space_node),
	expression_(expression_node),
	post_expression_space_(post_expression_space_node),
	post_closing_bracket_space_(post_closing_bracket_space_node),
	statement_(new statement(statement_node))
{
	update_node_list();
}

for_statement::for_statement(const for_statement& o):
	composite_node(),
	post_for_keyword_space_(o.post_for_keyword_space_),
	post_opening_bracket_space_(o.post_opening_bracket_space_),
	for_init_statement_(o.for_init_statement_),
	post_for_init_statement_space_(o.post_for_init_statement_space_),
	condition_(o.condition_),
	post_condition_space_(o.post_condition_space_),
	post_semicolon_space_(o.post_semicolon_space_),
	expression_(o.expression_),
	post_expression_space_(o.post_expression_space_),
	post_closing_bracket_space_(o.post_closing_bracket_space_),
	statement_(new statement(*o.statement_))
{
	update_node_list();
}

for_statement::for_statement(for_statement&& o):
	composite_node(),
	post_for_keyword_space_(std::move(o.post_for_keyword_space_)),
	post_opening_bracket_space_(std::move(o.post_opening_bracket_space_)),
	for_init_statement_(std::move(o.for_init_statement_)),
	post_for_init_statement_space_(std::move(o.post_for_init_statement_space_)),
	condition_(std::move(o.condition_)),
	post_condition_space_(std::move(o.post_condition_space_)),
	post_semicolon_space_(std::move(o.post_semicolon_space_)),
	expression_(std::move(o.expression_)),
	post_expression_space_(std::move(o.post_expression_space_)),
	post_closing_bracket_space_(std::move(o.post_closing_bracket_space_)),
	statement_(std::move(o.statement_))
{
	update_node_list();
}

const for_statement&
for_statement::operator=(const for_statement& o)
{
	post_for_keyword_space_ = o.post_for_keyword_space_;
	post_opening_bracket_space_ = o.post_opening_bracket_space_;
	for_init_statement_ = o.for_init_statement_;
	post_for_init_statement_space_ = o.post_for_init_statement_space_;
	condition_ = o.condition_;
	post_condition_space_ = o.post_condition_space_;
	post_semicolon_space_ = o.post_semicolon_space_;
	expression_ = o.expression_;
	post_expression_space_ = o.post_expression_space_;
	post_closing_bracket_space_ = o.post_closing_bracket_space_;
	statement_ = std::move(std::unique_ptr<statement>(new statement(*o.statement_)));

	update_node_list();

	return *this;
}

void
for_statement::update_node_list()
{
	clear();
	add(global_nodes::for_keyword);
	if(post_for_keyword_space_) add(*post_for_keyword_space_);
	add(global_nodes::opening_bracket);
	if(post_opening_bracket_space_) add(*post_opening_bracket_space_);
	if(for_init_statement_) add(*for_init_statement_);
	if(post_for_init_statement_space_) add(*post_for_init_statement_space_);
	if(condition_) add(*condition_);
	if(post_condition_space_) add(*post_condition_space_);
	add(global_nodes::semicolon);
	if(post_semicolon_space_) add(*post_semicolon_space_);
	if(expression_) add(*expression_);
	if(post_expression_space_) add(*post_expression_space_);
	add(global_nodes::closing_bracket);
	if(post_closing_bracket_space_) add(*post_closing_bracket_space_);
	add(*statement_);
}

}}} //namespace socoa::cpp::syntax_nodes

