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

#include "member_specification_access_specifier.hpp"

#include "common_nodes.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

member_specification_access_specifier::member_specification_access_specifier
(
    access_specifier&& a_access_specifier,
	boost::optional<space>&& post_access_specifier_node
):
    access_specifier_(std::move(a_access_specifier)),
	post_access_specifier_(post_access_specifier_node)
{
	update_node_list();
}

member_specification_access_specifier::member_specification_access_specifier(const member_specification_access_specifier& o):
	composite_node(),
    access_specifier_(o.access_specifier_),
	post_access_specifier_(o.post_access_specifier_)
{
	update_node_list();
}

member_specification_access_specifier::member_specification_access_specifier(member_specification_access_specifier&& o):
    access_specifier_(std::move(o.access_specifier_)),
	post_access_specifier_(std::move(o.post_access_specifier_))
{
	update_node_list();
}

const member_specification_access_specifier&
member_specification_access_specifier::operator=(const member_specification_access_specifier& o)
{
    access_specifier_ = o.access_specifier_;
	post_access_specifier_ = o.post_access_specifier_;
	update_node_list();

	return *this;
}

void
member_specification_access_specifier::update_node_list()
{
	clear();
	add(access_specifier_);
	if(post_access_specifier_) add(*post_access_specifier_);
	add(colon);
}

}}} //namespace socoa::cpp::syntax_nodes
