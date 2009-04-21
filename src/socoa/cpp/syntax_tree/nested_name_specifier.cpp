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

#include "nested_name_specifier.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

nested_name_specifier::nested_name_specifier
(
	identifier_or_template_id&& an_identifier_or_template_id,
	boost::optional<next_part_seq>&& a_next_part_seq
):
	identifier_or_template_id_(std::move(an_identifier_or_template_id)),
	next_part_seq_(std::move(a_next_part_seq))
{
	update_node_list();
}

nested_name_specifier::nested_name_specifier(const nested_name_specifier& o):
	composite_node(),
	identifier_or_template_id_(o.identifier_or_template_id_),
	next_part_seq_(o.next_part_seq_)
{
	update_node_list();
}

nested_name_specifier::nested_name_specifier(nested_name_specifier&& o):
	identifier_or_template_id_(std::move(o.identifier_or_template_id_)),
	next_part_seq_(std::move(o.next_part_seq_))
{
	update_node_list();
}

const nested_name_specifier&
nested_name_specifier::operator=(const nested_name_specifier& o)
{
	identifier_or_template_id_ = o.identifier_or_template_id_;
	next_part_seq_ = o.next_part_seq_;

	update_node_list();

	return *this;
}

void
nested_name_specifier::update_node_list()
{
	clear();
	add(identifier_or_template_id_);
	if(next_part_seq_) add(*next_part_seq_);
}


nested_name_specifier::next_part::next_part
(
	bool template_keyword,
	identifier_or_template_id&& an_identifier_or_template_id
):
	template_keyword_(template_keyword),
	identifier_or_template_id_(an_identifier_or_template_id)
{
	update_node_list();
}

nested_name_specifier::next_part::next_part(const next_part& o):
	composite_node(),
	template_keyword_(o.template_keyword_),
	identifier_or_template_id_(o.identifier_or_template_id_)
{
	update_node_list();
}

nested_name_specifier::next_part::next_part(next_part&& o):
	template_keyword_(std::move(o.template_keyword_)),
	identifier_or_template_id_(std::move(o.identifier_or_template_id_))
{
	update_node_list();
}

const nested_name_specifier::next_part&
nested_name_specifier::next_part::operator=(const next_part& o)
{
	template_keyword_ = o.template_keyword_;
	identifier_or_template_id_ = o.identifier_or_template_id_;
	update_node_list();

	return *this;
}

void
nested_name_specifier::next_part::update_node_list()
{
	clear();
	add(identifier_or_template_id_);
}

}}} //namespace socoa::cpp::syntax_tree
