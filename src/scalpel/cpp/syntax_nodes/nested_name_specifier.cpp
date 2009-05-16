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

#include "nested_name_specifier.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

nested_name_specifier::nested_name_specifier
(
	identifier_or_template_id&& an_identifier_or_template_id,
	optional_node<space>&& post_identifier_or_template_id_space_node,
	optional_node<space>&& pre_last_part_seq_space_node,
	optional_node<last_part_seq>&& a_last_part_seq
):
	identifier_or_template_id_(std::move(an_identifier_or_template_id)),
	post_identifier_or_template_id_space_(post_identifier_or_template_id_space_node),
	pre_last_part_seq_space_(pre_last_part_seq_space_node),
	last_part_seq_(std::move(a_last_part_seq))
{
	update_node_list();
}

nested_name_specifier::nested_name_specifier(const nested_name_specifier& o):
	composite_node(),
	identifier_or_template_id_(o.identifier_or_template_id_),
	post_identifier_or_template_id_space_(o.post_identifier_or_template_id_space_),
	pre_last_part_seq_space_(o.pre_last_part_seq_space_),
	last_part_seq_(o.last_part_seq_)
{
	update_node_list();
}

nested_name_specifier::nested_name_specifier(nested_name_specifier&& o):
	identifier_or_template_id_(std::move(o.identifier_or_template_id_)),
	post_identifier_or_template_id_space_(std::move(o.post_identifier_or_template_id_space_)),
	pre_last_part_seq_space_(std::move(o.pre_last_part_seq_space_)),
	last_part_seq_(std::move(o.last_part_seq_))
{
	update_node_list();
}

const nested_name_specifier&
nested_name_specifier::operator=(const nested_name_specifier& o)
{
	identifier_or_template_id_ = o.identifier_or_template_id_;
	post_identifier_or_template_id_space_ = o.post_identifier_or_template_id_space_;
	pre_last_part_seq_space_ = o.pre_last_part_seq_space_;
	last_part_seq_ = o.last_part_seq_;

	update_node_list();

	return *this;
}

void
nested_name_specifier::update_node_list()
{
	clear();
	add(identifier_or_template_id_);
	if(post_identifier_or_template_id_space_) add(*post_identifier_or_template_id_space_);
	add(common_nodes::double_colon);
	if(pre_last_part_seq_space_) add(*pre_last_part_seq_space_);
	if(last_part_seq_) add(*last_part_seq_);
}


nested_name_specifier::last_part::last_part
(
	bool template_keyword,
	identifier_or_template_id&& an_identifier_or_template_id
):
	template_keyword_(template_keyword),
	identifier_or_template_id_(an_identifier_or_template_id)
{
	update_node_list();
}

nested_name_specifier::last_part::last_part(const last_part& o):
	composite_node(),
	template_keyword_(o.template_keyword_),
	identifier_or_template_id_(o.identifier_or_template_id_)
{
	update_node_list();
}

nested_name_specifier::last_part::last_part(last_part&& o):
	template_keyword_(std::move(o.template_keyword_)),
	identifier_or_template_id_(std::move(o.identifier_or_template_id_))
{
	update_node_list();
}

const nested_name_specifier::last_part&
nested_name_specifier::last_part::operator=(const last_part& o)
{
	template_keyword_ = o.template_keyword_;
	identifier_or_template_id_ = o.identifier_or_template_id_;
	update_node_list();

	return *this;
}

void
nested_name_specifier::last_part::update_node_list()
{
	clear();
	add(identifier_or_template_id_);
	add(common_nodes::double_colon);
}

}}} //namespace scalpel::cpp::syntax_nodes
