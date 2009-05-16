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

#include "default_statement.hpp"

#include "common_nodes.hpp"
#include "statement.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

default_statement::default_statement
(
	optional_node<space>&& post_default_keyword_space_node,
	optional_node<space>&& post_colon_space_node,
	statement&& statement_node
):
	post_default_keyword_space_(post_default_keyword_space_node),
	post_colon_space_(post_colon_space_node),
	statement_(new statement(statement_node))
{
	update_node_list();
}

default_statement::default_statement(const default_statement& o):
	composite_node(),
	post_default_keyword_space_(o.post_default_keyword_space_),
	post_colon_space_(o.post_colon_space_),
	statement_(new statement(*o.statement_))
{
	update_node_list();
}

default_statement::default_statement(default_statement&& o):
	composite_node(),
	post_default_keyword_space_(std::move(o.post_default_keyword_space_)),
	post_colon_space_(std::move(o.post_colon_space_)),
	statement_(std::move(o.statement_))
{
	update_node_list();
}

const default_statement&
default_statement::operator=(const default_statement& o)
{
	post_default_keyword_space_ = o.post_default_keyword_space_;
	post_colon_space_ = o.post_colon_space_;
	statement_ = std::move(std::unique_ptr<statement>(new statement(*o.statement_)));

	update_node_list();

	return *this;
}

void
default_statement::update_node_list()
{
	clear();
	add(common_nodes::default_keyword);
	if(post_default_keyword_space_) add(*post_default_keyword_space_);
	add(common_nodes::colon);
	if(post_colon_space_) add(*post_colon_space_);
	add(*statement_);
}

}}} //namespace scalpel::cpp::syntax_nodes

