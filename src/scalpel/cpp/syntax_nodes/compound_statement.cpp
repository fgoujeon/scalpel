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

#include "compound_statement.hpp"

#include "common_nodes.hpp"
#include "statement_seq.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

compound_statement::compound_statement
(
	optional_node<space>&& post_opening_brace_space,
	optional_node<statement_seq>&& statement_seq_node,
	optional_node<space>&& post_statement_seq_space
):
	post_opening_brace_space_(post_opening_brace_space),
	statement_seq_(new optional_node<statement_seq>(statement_seq_node)),
	post_statement_seq_space_(post_statement_seq_space)
{
	update_node_list();
}

compound_statement::compound_statement(const compound_statement& o):
	composite_node(),
	post_opening_brace_space_(o.post_opening_brace_space_),
	statement_seq_(new optional_node<statement_seq>(*o.statement_seq_)),
	post_statement_seq_space_(o.post_statement_seq_space_)
{
	update_node_list();
}

compound_statement::compound_statement(compound_statement&& o):
	composite_node(),
	post_opening_brace_space_(std::move(o.post_opening_brace_space_)),
	statement_seq_(o.statement_seq_),
	post_statement_seq_space_(std::move(o.post_statement_seq_space_))
{
	o.statement_seq_ = new optional_node<statement_seq>();
	update_node_list();
}

compound_statement::~compound_statement()
{
	delete statement_seq_;
}

const compound_statement&
compound_statement::operator=(const compound_statement& o)
{
	compound_statement copy(o);
	std::swap(copy, *this);
	return *this;
}

void
compound_statement::update_node_list()
{
	clear();
	add(common_nodes::opening_brace);
	if(post_opening_brace_space_) add(*post_opening_brace_space_);
	if(*statement_seq_) add(**statement_seq_);
	if(post_statement_seq_space_) add(*post_statement_seq_space_);
	add(common_nodes::closing_brace);
}

}}} //namespace scalpel::cpp::syntax_nodes

