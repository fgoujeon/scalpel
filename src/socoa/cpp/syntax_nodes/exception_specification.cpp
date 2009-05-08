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

#include "exception_specification.hpp"

#include "common_nodes.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

exception_specification::exception_specification
(
	boost::optional<space>&& post_throw_keyword_space_node,
	boost::optional<space>&& post_opening_bracket_space_node,
	boost::optional<type_id_list>&& type_id_list_node,
	boost::optional<space>&& post_type_id_list_space_node
):
	post_throw_keyword_space_(post_throw_keyword_space_node),
	post_opening_bracket_space_(post_opening_bracket_space_node),
	type_id_list_(type_id_list_node),
	post_type_id_list_space_(post_type_id_list_space_node)
{
	update_node_list();
}

exception_specification::exception_specification(const exception_specification& o):
	composite_node(),
	post_throw_keyword_space_(o.post_throw_keyword_space_),
	post_opening_bracket_space_(o.post_opening_bracket_space_),
	type_id_list_(o.type_id_list_),
	post_type_id_list_space_(o.post_type_id_list_space_)
{
	update_node_list();
}

exception_specification::exception_specification(exception_specification&& o):
	composite_node(),
	post_throw_keyword_space_(std::move(o.post_throw_keyword_space_)),
	post_opening_bracket_space_(std::move(o.post_opening_bracket_space_)),
	type_id_list_(std::move(o.type_id_list_)),
	post_type_id_list_space_(std::move(o.post_type_id_list_space_))
{
	update_node_list();
}

const exception_specification&
exception_specification::operator=(const exception_specification& o)
{
	post_throw_keyword_space_ = o.post_throw_keyword_space_;
	post_opening_bracket_space_ = o.post_opening_bracket_space_;
	type_id_list_ = o.type_id_list_;
	post_type_id_list_space_ = o.post_type_id_list_space_;

	update_node_list();

	return *this;
}

void
exception_specification::update_node_list()
{
	clear();
	add(global_nodes::throw_keyword);
	if(post_throw_keyword_space_) add(*post_throw_keyword_space_);
	add(global_nodes::opening_bracket);
	if(post_opening_bracket_space_) add(*post_opening_bracket_space_);
	if(type_id_list_) add(*type_id_list_);
	if(post_type_id_list_space_) add(*post_type_id_list_space_);
	add(global_nodes::closing_bracket);
}

}}} //namespace socoa::cpp::syntax_nodes

