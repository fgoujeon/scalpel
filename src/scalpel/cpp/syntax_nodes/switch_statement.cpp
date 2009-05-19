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

#include "switch_statement.hpp"

#include "common_nodes.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

switch_statement::switch_statement
(
	optional_node<space>&& post_switch_keyword_space_node,
	optional_node<space>&& post_opening_bracket_space_node,
	condition&& condition_node,
	optional_node<space>&& post_condition_space_node,
	optional_node<space>&& post_closing_bracket_space_node,
	statement&& statement_node
):
	post_switch_keyword_space_(post_switch_keyword_space_node),
	post_opening_bracket_space_(post_opening_bracket_space_node),
	condition_(condition_node),
	post_condition_space_(post_condition_space_node),
	post_closing_bracket_space_(post_closing_bracket_space_node),
	statement_(statement_node)
{
	update_node_list();
}

switch_statement::switch_statement(const switch_statement& o):
	composite_node(),
	post_switch_keyword_space_(o.post_switch_keyword_space_),
	post_opening_bracket_space_(o.post_opening_bracket_space_),
	condition_(o.condition_),
	post_condition_space_(o.post_condition_space_),
	post_closing_bracket_space_(o.post_closing_bracket_space_),
	statement_(o.statement_)
{
	update_node_list();
}

switch_statement::switch_statement(switch_statement&& o):
	composite_node(),
	post_switch_keyword_space_(std::move(o.post_switch_keyword_space_)),
	post_opening_bracket_space_(std::move(o.post_opening_bracket_space_)),
	condition_(std::move(o.condition_)),
	post_condition_space_(std::move(o.post_condition_space_)),
	post_closing_bracket_space_(std::move(o.post_closing_bracket_space_)),
	statement_(std::move(o.statement_))
{
	update_node_list();
}

const switch_statement&
switch_statement::operator=(const switch_statement& o)
{
	post_switch_keyword_space_ = o.post_switch_keyword_space_;
	post_opening_bracket_space_ = o.post_opening_bracket_space_;
	condition_ = o.condition_;
	post_condition_space_ = o.post_condition_space_;
	post_closing_bracket_space_ = o.post_closing_bracket_space_;
	statement_ = o.statement_;

	update_node_list();

	return *this;
}

void
switch_statement::update_node_list()
{
	clear();
	add(common_nodes::switch_keyword);
	if(post_switch_keyword_space_) add(*post_switch_keyword_space_);
	add(common_nodes::opening_round_bracket);
	if(post_opening_bracket_space_) add(*post_opening_bracket_space_);
	add(condition_);
	if(post_condition_space_) add(*post_condition_space_);
	add(common_nodes::closing_round_bracket);
	if(post_closing_bracket_space_) add(*post_closing_bracket_space_);
	add(statement_);
}

}}} //namespace scalpel::cpp::syntax_nodes

