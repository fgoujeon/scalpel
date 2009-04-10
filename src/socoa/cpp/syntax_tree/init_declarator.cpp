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

#include "init_declarator.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

init_declarator::init_declarator(declarator&& a_declarator):
	declarator_(std::move(a_declarator))
{
	update_node_list();
}

init_declarator::init_declarator(const init_declarator& o):
	composite_node(),
	declarator_(o.declarator_)
{
	update_node_list();
}

init_declarator::init_declarator(init_declarator&& o):
	declarator_(std::move(o.declarator_))
{
	update_node_list();
}

const init_declarator&
init_declarator::operator=(const init_declarator& o)
{
	declarator_ = o.declarator_;
	update_node_list();

	return *this;
}

void
init_declarator::update_node_list()
{
	clear();
	add(declarator_);
}

}}} //namespace socoa::cpp::syntax_tree
