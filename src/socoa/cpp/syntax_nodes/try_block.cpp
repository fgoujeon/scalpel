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

#include "try_block.hpp"

#include "common_nodes.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

try_block::try_block
(
	boost::optional<space>&& post_try_keyword_space_node,
	compound_statement&& compound_statement_node,
	boost::optional<space>&& post_compound_statement_space_node,
	handler_seq&& handler_seq_node
):
	post_try_keyword_space_(post_try_keyword_space_node),
	compound_statement_(compound_statement_node),
	post_compound_statement_space_(post_compound_statement_space_node),
	handler_seq_(handler_seq_node)
{
	update_node_list();
}

try_block::try_block(const try_block& o):
	composite_node(),
	post_try_keyword_space_(o.post_try_keyword_space_),
	compound_statement_(o.compound_statement_),
	post_compound_statement_space_(o.post_compound_statement_space_),
	handler_seq_(o.handler_seq_)
{
	update_node_list();
}

try_block::try_block(try_block&& o):
	composite_node(),
	post_try_keyword_space_(std::move(o.post_try_keyword_space_)),
	compound_statement_(std::move(o.compound_statement_)),
	post_compound_statement_space_(std::move(o.post_compound_statement_space_)),
	handler_seq_(std::move(o.handler_seq_))
{
	update_node_list();
}

const try_block&
try_block::operator=(const try_block& o)
{
	post_try_keyword_space_ = o.post_try_keyword_space_;
	compound_statement_ = o.compound_statement_;
	post_compound_statement_space_ = o.post_compound_statement_space_;
	handler_seq_ = o.handler_seq_;

	update_node_list();

	return *this;
}

void
try_block::update_node_list()
{
	clear();
	add(try_keyword);
	if(post_try_keyword_space_) add(*post_try_keyword_space_);
	add(compound_statement_);
	if(post_compound_statement_space_) add(*post_compound_statement_space_);
	add(handler_seq_);
}

}}} //namespace socoa::cpp::syntax_nodes

