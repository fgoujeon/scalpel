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

#include "classic_labeled_statement.hpp"

#include "common_nodes.hpp"
#include "statement.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

classic_labeled_statement::classic_labeled_statement
(
	identifier&& identifier_node,
	optional_node<space>&& post_identifier_space_node,
	optional_node<space>&& post_colon_space_node,
	statement&& statement_node
):
	identifier_(identifier_node),
	post_identifier_space_(post_identifier_space_node),
	post_colon_space_(post_colon_space_node),
	statement_(new statement(statement_node))
{
	update_node_list();
}

classic_labeled_statement::classic_labeled_statement(const classic_labeled_statement& o):
	composite_node(),
	identifier_(o.identifier_),
	post_identifier_space_(o.post_identifier_space_),
	post_colon_space_(o.post_colon_space_),
	statement_(new statement(*o.statement_))
{
	update_node_list();
}

classic_labeled_statement::classic_labeled_statement(classic_labeled_statement&& o):
	composite_node(),
	identifier_(std::move(o.identifier_)),
	post_identifier_space_(std::move(o.post_identifier_space_)),
	post_colon_space_(std::move(o.post_colon_space_)),
	statement_(std::move(o.statement_))
{
	update_node_list();
}

const classic_labeled_statement&
classic_labeled_statement::operator=(const classic_labeled_statement& o)
{
	classic_labeled_statement copy(o);
	std::swap(copy, *this);
	return *this;
}

void
classic_labeled_statement::update_node_list()
{
	clear();
	add(identifier_);
	if(post_identifier_space_) add(*post_identifier_space_);
	add(common_nodes::colon);
	if(post_colon_space_) add(*post_colon_space_);
	add(*statement_);
}

}}} //namespace scalpel::cpp::syntax_nodes

