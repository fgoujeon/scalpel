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

#include "if_statement.hpp"

#include "statement.hpp"
#include "common_nodes.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

if_statement::if_statement
(
	boost::optional<space>&& post_if_keyword_space_node,
	boost::optional<space>&& post_opening_bracket_space_node,
	condition&& condition_node,
	boost::optional<space>&& post_condition_space_node,
	boost::optional<space>&& post_closing_bracket_space_node,
	statement&& statement_node,
	boost::optional<space>&& pre_else_keyword_space_node,
	boost::optional<statement>&& else_statement_node,
	boost::optional<space>&& post_else_keyword_space_node
):
	post_if_keyword_space_(post_if_keyword_space_node),
	post_opening_bracket_space_(post_opening_bracket_space_node),
	condition_(condition_node),
	post_condition_space_(post_condition_space_node),
	post_closing_bracket_space_(post_closing_bracket_space_node),
	statement_(new statement(statement_node)),
	pre_else_keyword_space_(pre_else_keyword_space_node),
	post_else_keyword_space_(post_else_keyword_space_node)
{
	if(else_statement_node)
		else_statement_ = std::move(std::unique_ptr<statement>(new statement(*else_statement_node)));

	update_node_list();
}

if_statement::if_statement(const if_statement& o):
	composite_node(),
	post_if_keyword_space_(o.post_if_keyword_space_),
	post_opening_bracket_space_(o.post_opening_bracket_space_),
	condition_(o.condition_),
	post_condition_space_(o.post_condition_space_),
	post_closing_bracket_space_(o.post_closing_bracket_space_),
	statement_(new statement(*o.statement_)),
	pre_else_keyword_space_(o.pre_else_keyword_space_),
	post_else_keyword_space_(o.post_else_keyword_space_)
{
	if(o.else_statement_)
		else_statement_ = std::move(std::unique_ptr<statement>(new statement(*o.else_statement_)));

	update_node_list();
}

if_statement::if_statement(if_statement&& o):
	composite_node(),
	post_if_keyword_space_(std::move(o.post_if_keyword_space_)),
	post_opening_bracket_space_(std::move(o.post_opening_bracket_space_)),
	condition_(std::move(o.condition_)),
	post_condition_space_(std::move(o.post_condition_space_)),
	post_closing_bracket_space_(std::move(o.post_closing_bracket_space_)),
	statement_(std::move(o.statement_)),
	pre_else_keyword_space_(std::move(o.pre_else_keyword_space_)),
	else_statement_(std::move(o.else_statement_)),
	post_else_keyword_space_(std::move(o.post_else_keyword_space_))
{
	update_node_list();
}

const if_statement&
if_statement::operator=(const if_statement& o)
{
	post_if_keyword_space_ = o.post_if_keyword_space_;
	post_opening_bracket_space_ = o.post_opening_bracket_space_;
	condition_ = o.condition_;
	post_condition_space_ = o.post_condition_space_;
	post_closing_bracket_space_ = o.post_closing_bracket_space_;
	statement_ = std::move(std::unique_ptr<statement>(new statement(*o.statement_)));
	pre_else_keyword_space_ = o.pre_else_keyword_space_;
	if(o.else_statement_)
		else_statement_ = std::move(std::unique_ptr<statement>(new statement(*o.else_statement_)));
	post_else_keyword_space_ = o.post_else_keyword_space_;

	update_node_list();

	return *this;
}

const boost::optional<const statement&>
if_statement::else_statement_node() const
{
	if(else_statement_)
		return boost::optional<const statement&>(*else_statement_);
	else
		return boost::optional<const statement&>();
}

void
if_statement::update_node_list()
{
	clear();
	add(common_nodes::if_keyword);
	if(post_if_keyword_space_) add(*post_if_keyword_space_);
	add(common_nodes::opening_round_bracket);
	if(post_opening_bracket_space_) add(*post_opening_bracket_space_);
	add(condition_);
	if(post_condition_space_) add(*post_condition_space_);
	add(common_nodes::closing_round_bracket);
	if(post_closing_bracket_space_) add(*post_closing_bracket_space_);
	add(*statement_);
	if(pre_else_keyword_space_) add(*pre_else_keyword_space_);
	if(else_statement_) add(common_nodes::else_keyword);
	if(post_else_keyword_space_) add(*post_else_keyword_space_);
	if(else_statement_) add(*else_statement_);
}

}}} //namespace scalpel::cpp::syntax_nodes

