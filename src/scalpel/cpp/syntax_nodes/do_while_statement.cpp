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

#include "do_while_statement.hpp"

#include "statement.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

do_while_statement::do_while_statement
(
	boost::optional<space>&& post_do_keyword_space_node,
	statement&& statement_node,
	boost::optional<space>&& post_statement_space_node,
	boost::optional<space>&& post_while_keyword_space_node,
	boost::optional<space>&& post_opening_bracket_space_node,
	expression&& expression_node,
	boost::optional<space>&& post_expression_space_node,
	boost::optional<space>&& post_closing_bracket_space_node
):
	post_do_keyword_space_(post_do_keyword_space_node),
	statement_(new statement(statement_node)),
	post_statement_space_(post_statement_space_node),
	post_while_keyword_space_(post_while_keyword_space_node),
	post_opening_bracket_space_(post_opening_bracket_space_node),
	expression_(expression_node),
	post_expression_space_(post_expression_space_node),
	post_closing_bracket_space_(post_closing_bracket_space_node)
{
	update_node_list();
}

do_while_statement::do_while_statement(const do_while_statement& o):
	composite_node(),
	post_do_keyword_space_(o.post_do_keyword_space_),
	statement_(new statement(*o.statement_)),
	post_statement_space_(o.post_statement_space_),
	post_while_keyword_space_(o.post_while_keyword_space_),
	post_opening_bracket_space_(o.post_opening_bracket_space_),
	expression_(o.expression_),
	post_expression_space_(o.post_expression_space_),
	post_closing_bracket_space_(o.post_closing_bracket_space_)
{
	update_node_list();
}

do_while_statement::do_while_statement(do_while_statement&& o):
	composite_node(),
	post_do_keyword_space_(std::move(o.post_do_keyword_space_)),
	statement_(std::move(o.statement_)),
	post_statement_space_(std::move(o.post_statement_space_)),
	post_while_keyword_space_(std::move(o.post_while_keyword_space_)),
	post_opening_bracket_space_(std::move(o.post_opening_bracket_space_)),
	expression_(std::move(o.expression_)),
	post_expression_space_(std::move(o.post_expression_space_)),
	post_closing_bracket_space_(std::move(o.post_closing_bracket_space_))
{
	update_node_list();
}

const do_while_statement&
do_while_statement::operator=(const do_while_statement& o)
{
	do_while_statement copy(o);
	std::swap(copy, *this);
	return *this;
}

void
do_while_statement::update_node_list()
{
	clear();
	add(global_nodes::do_keyword);
	if(post_do_keyword_space_) add(*post_do_keyword_space_);
	add(*statement_);
	if(post_statement_space_) add(*post_statement_space_);
	add(global_nodes::while_keyword);
	if(post_while_keyword_space_) add(*post_while_keyword_space_);
	add(global_nodes::opening_bracket);
	if(post_opening_bracket_space_) add(*post_opening_bracket_space_);
	add(expression_);
	if(post_expression_space_) add(*post_expression_space_);
	add(global_nodes::closing_bracket);
	if(post_closing_bracket_space_) add(*post_closing_bracket_space_);
	add(global_nodes::semicolon);
}

}}} //namespace scalpel::cpp::syntax_nodes

