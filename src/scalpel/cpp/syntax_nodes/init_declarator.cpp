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

#include "init_declarator.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

init_declarator::init_declarator
(
	declarator&& a_declarator,
	boost::optional<space>&& space_node,
	boost::optional<initializer>&& initializer_node
):
	declarator_(std::move(a_declarator)),
	space_(space_node),
	initializer_(initializer_node)
{
	update_node_list();
}

init_declarator::init_declarator(const init_declarator& o):
	composite_node(),
	declarator_(o.declarator_),
	space_(o.space_),
	initializer_(o.initializer_)
{
	update_node_list();
}

init_declarator::init_declarator(init_declarator&& o):
	composite_node(),
	declarator_(std::move(o.declarator_)),
	space_(std::move(o.space_)),
	initializer_(std::move(o.initializer_))
{
	update_node_list();
}

const init_declarator&
init_declarator::operator=(const init_declarator& o)
{
	declarator_ = o.declarator_;
	space_ = o.space_;
	initializer_ = o.initializer_;

	update_node_list();

	return *this;
}

void
init_declarator::update_node_list()
{
	clear();
	add(declarator_);
	if(space_) add(*space_);
	if(initializer_) add(*initializer_);
}

}}} //namespace scalpel::cpp::syntax_nodes
