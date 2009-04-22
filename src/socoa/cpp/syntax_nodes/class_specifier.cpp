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

#include "class_specifier.hpp"

#include "member_specification.hpp"
#include "class_head.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

class_specifier::class_specifier
(
    class_head&& head,
    boost::optional<member_specification>&& a_member_specification
):
    class_head_(std::move(head))
{
	if(a_member_specification)
	{
		member_specification_ = std::make_shared<member_specification>(std::move(*a_member_specification));
	}
	update_node_list();
}

class_specifier::class_specifier(const class_specifier& o):
	composite_node(),
    class_head_(o.class_head_),
    member_specification_(o.member_specification_)
{
	update_node_list();
}

class_specifier::class_specifier(class_specifier&& o):
    class_head_(std::move(o.class_head_)),
    member_specification_(std::move(o.member_specification_))
{
	update_node_list();
}

const class_specifier&
class_specifier::operator=(const class_specifier& o)
{
    class_head_ = o.class_head_;
    member_specification_ = o.member_specification_;
	update_node_list();

	return *this;
}

void
class_specifier::update_node_list()
{
	clear();
    add(class_head_);
	if(member_specification_) add(*member_specification_);
}

}}} //namespace socoa::cpp::syntax_nodes
