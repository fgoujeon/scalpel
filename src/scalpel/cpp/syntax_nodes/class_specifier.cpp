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

#include "class_specifier.hpp"

#include "member_specification.hpp"
#include "class_head.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class_specifier::class_specifier
(
	class_head&& class_head_node,
	optional_node<space>&& post_class_head_space_node,
	optional_node<space>&& post_opening_brace_space_node,
	optional_node<member_specification>&& member_specification_node,
	optional_node<space>&& post_member_specification_space_node
):
    class_head_(std::move(class_head_node)),
	post_class_head_space_(post_class_head_space_node),
	post_opening_brace_space_(post_opening_brace_space_node),
	member_specification_(new optional_node<member_specification>(member_specification_node)),
	post_member_specification_space_(post_member_specification_space_node)
{
	update_node_list();
}

class_specifier::class_specifier(const class_specifier& o):
	composite_node(),
    class_head_(o.class_head_),
	post_class_head_space_(o.post_class_head_space_),
	post_opening_brace_space_(o.post_opening_brace_space_),
	member_specification_(new optional_node<member_specification>(*o.member_specification_)),
	post_member_specification_space_(o.post_member_specification_space_)
{
	update_node_list();
}

class_specifier::class_specifier(class_specifier&& o):
    class_head_(std::move(o.class_head_)),
	post_class_head_space_(std::move(o.post_class_head_space_)),
	post_opening_brace_space_(std::move(o.post_opening_brace_space_)),
    member_specification_(o.member_specification_),
	post_member_specification_space_(std::move(o.post_member_specification_space_))
{
	o.member_specification_ = new optional_node<member_specification>();
	update_node_list();
}

class_specifier::~class_specifier()
{
	delete member_specification_;
}

const class_specifier&
class_specifier::operator=(const class_specifier& o)
{
	class_specifier copy(o);
	std::swap(copy, *this);
	return *this;
}

void
class_specifier::update_node_list()
{
	clear();
    add(class_head_);
	if(post_class_head_space_) add(*post_class_head_space_);
	add(common_nodes::opening_brace);
	if(post_opening_brace_space_) add(*post_opening_brace_space_);
    if(*member_specification_) add(**member_specification_);
	if(post_member_specification_space_) add(*post_member_specification_space_);
	add(common_nodes::closing_brace);
}

}}} //namespace scalpel::cpp::syntax_nodes
