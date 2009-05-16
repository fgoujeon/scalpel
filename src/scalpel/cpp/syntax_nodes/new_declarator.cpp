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

#include "new_declarator.hpp"

#include "direct_new_declarator.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

new_declarator::new_declarator
(
	optional_node<ptr_operator_seq>&& ptr_operator_seq_node,
	optional_node<space>&& space_node,
	optional_node<direct_new_declarator>&& direct_new_declarator_node
):
	ptr_operator_seq_(ptr_operator_seq_node),
	space_(space_node)
{
	if(direct_new_declarator_node)
		direct_new_declarator_ = new direct_new_declarator(*direct_new_declarator_node);
	else
		direct_new_declarator_ = 0;
	update_node_list();
}

new_declarator::new_declarator(const new_declarator& o):
	composite_node(),
	ptr_operator_seq_(o.ptr_operator_seq_),
	space_(o.space_)
{
	if(o.direct_new_declarator_)
		direct_new_declarator_ = new direct_new_declarator(*o.direct_new_declarator_);
	else
		direct_new_declarator_ = 0;
	update_node_list();
}

new_declarator::new_declarator(new_declarator&& o):
	composite_node(),
	ptr_operator_seq_(std::move(o.ptr_operator_seq_)),
	space_(std::move(o.space_)),
	direct_new_declarator_(o.direct_new_declarator_)
{
	o.direct_new_declarator_ = 0;
	update_node_list();
}

new_declarator::~new_declarator()
{
	delete direct_new_declarator_;
}

const new_declarator&
new_declarator::operator=(const new_declarator& o)
{
	new_declarator copy(o);
	delete direct_new_declarator_;
	std::swap(copy, *this);
	return *this;
}

void
new_declarator::update_node_list()
{
	clear();
	if(ptr_operator_seq_) add(*ptr_operator_seq_);
	if(space_) add(*space_);
	if(direct_new_declarator_) add(*direct_new_declarator_);
}

}}} //namespace scalpel::cpp::syntax_nodes

