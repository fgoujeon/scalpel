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

#include "compound_statement.hpp"

#include "common_nodes.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

compound_statement::compound_statement
(
	boost::optional<space>&& post_opening_brace_space,
	boost::optional<space>&& post_statement_seq_space
):
	post_opening_brace_space_(post_opening_brace_space),
	post_statement_seq_space_(post_statement_seq_space)
{
	update_node_list();
}

compound_statement::compound_statement(const compound_statement& o):
	composite_node(),
	post_opening_brace_space_(o.post_opening_brace_space_),
	post_statement_seq_space_(o.post_statement_seq_space_)
{
	update_node_list();
}

compound_statement::compound_statement(compound_statement&& o):
	composite_node(),
	post_opening_brace_space_(std::move(o.post_opening_brace_space_)),
	post_statement_seq_space_(std::move(o.post_statement_seq_space_))
{
	update_node_list();
}

const compound_statement&
compound_statement::operator=(const compound_statement& o)
{
	post_opening_brace_space_ = o.post_opening_brace_space_;
	post_statement_seq_space_ = o.post_statement_seq_space_;

	update_node_list();

	return *this;
}

void
compound_statement::update_node_list()
{
	clear();

	add(opening_brace);
	if(post_opening_brace_space_) add(*post_opening_brace_space_);
	if(post_statement_seq_space_) add(*post_statement_seq_space_);
	add(closing_brace);
}

}}} //namespace socoa::cpp::syntax_tree

