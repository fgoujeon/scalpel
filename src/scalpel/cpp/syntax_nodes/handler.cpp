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

#include "handler.hpp"

#include "common_nodes.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

handler::handler
(
	boost::optional<space>&& post_catch_keyword_space_node,
	boost::optional<space>&& post_opening_bracket_space_node,
	exception_declaration&& exception_declaration_node,
	boost::optional<space>&& post_exception_declaration_space_node,
	boost::optional<space>&& post_closing_bracket_space_node,
	compound_statement&& compound_statement_node
):
	post_catch_keyword_space_(post_catch_keyword_space_node),
	post_opening_bracket_space_(post_opening_bracket_space_node),
	exception_declaration_(exception_declaration_node),
	post_exception_declaration_space_(post_exception_declaration_space_node),
	post_closing_bracket_space_(post_closing_bracket_space_node),
	compound_statement_(compound_statement_node)
{
	update_node_list();
}

handler::handler(const handler& o):
	composite_node(),
	post_catch_keyword_space_(o.post_catch_keyword_space_),
	post_opening_bracket_space_(o.post_opening_bracket_space_),
	exception_declaration_(o.exception_declaration_),
	post_exception_declaration_space_(o.post_exception_declaration_space_),
	post_closing_bracket_space_(o.post_closing_bracket_space_),
	compound_statement_(o.compound_statement_)
{
	update_node_list();
}

handler::handler(handler&& o):
	composite_node(),
	post_catch_keyword_space_(std::move(o.post_catch_keyword_space_)),
	post_opening_bracket_space_(std::move(o.post_opening_bracket_space_)),
	exception_declaration_(std::move(o.exception_declaration_)),
	post_exception_declaration_space_(std::move(o.post_exception_declaration_space_)),
	post_closing_bracket_space_(std::move(o.post_closing_bracket_space_)),
	compound_statement_(std::move(o.compound_statement_))
{
	update_node_list();
}

const handler&
handler::operator=(const handler& o)
{
	post_catch_keyword_space_ = o.post_catch_keyword_space_;
	post_opening_bracket_space_ = o.post_opening_bracket_space_;
	exception_declaration_ = o.exception_declaration_;
	post_exception_declaration_space_ = o.post_exception_declaration_space_;
	post_closing_bracket_space_ = o.post_closing_bracket_space_;
	compound_statement_ = o.compound_statement_;

	update_node_list();

	return *this;
}

void
handler::update_node_list()
{
	clear();
	add(global_nodes::catch_keyword);
	if(post_catch_keyword_space_) add(*post_catch_keyword_space_);
	add(global_nodes::opening_bracket);
	if(post_opening_bracket_space_) add(*post_opening_bracket_space_);
	add(exception_declaration_);
	if(post_exception_declaration_space_) add(*post_exception_declaration_space_);
	add(global_nodes::closing_bracket);
	if(post_closing_bracket_space_) add(*post_closing_bracket_space_);
	add(compound_statement_);
}

}}} //namespace scalpel::cpp::syntax_nodes

