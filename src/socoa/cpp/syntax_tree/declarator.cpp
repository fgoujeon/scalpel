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

#include "declarator.hpp"

#include "direct_declarator.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

declarator::declarator
(
	boost::optional<ptr_operator_seq>&& ptr_operator_seq,
	boost::optional<space>&& post_ptr_operator_seq_space_node,
    direct_declarator&& a_direct_declarator
):
    ptr_operator_seq_(std::move(ptr_operator_seq)),
	post_ptr_operator_seq_space_node_(post_ptr_operator_seq_space_node),
    direct_declarator_(std::make_shared<direct_declarator>(std::move(a_direct_declarator)))
{
	update_node_list();
}

declarator::declarator(const declarator& o):
	composite_node(),
    ptr_operator_seq_(o.ptr_operator_seq_),
	post_ptr_operator_seq_space_node_(o.post_ptr_operator_seq_space_node_),
    direct_declarator_(o.direct_declarator_)
{
	update_node_list();
}

declarator::declarator(declarator&& o):
    ptr_operator_seq_(std::move(o.ptr_operator_seq_)),
	post_ptr_operator_seq_space_node_(std::move(o.post_ptr_operator_seq_space_node_)),
    direct_declarator_(std::move(o.direct_declarator_))
{
	update_node_list();
}

const declarator&
declarator::operator=(const declarator& o)
{
    ptr_operator_seq_ = o.ptr_operator_seq_;
	post_ptr_operator_seq_space_node_ = o.post_ptr_operator_seq_space_node_;
    direct_declarator_ = o.direct_declarator_;
	update_node_list();

	return *this;
}

void
declarator::update_node_list()
{
	clear();
	if(ptr_operator_seq_) add(*ptr_operator_seq_);
	if(post_ptr_operator_seq_space_node_) add(*post_ptr_operator_seq_space_node_);
	add(*direct_declarator_);
}

}}} //namespace socoa::cpp::syntax_tree
