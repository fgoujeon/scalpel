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

#include "member_declaration_function_definition.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

member_declaration_function_definition::member_declaration_function_definition
(
    function_definition&& a_function_definition
):
    function_definition_(std::move(a_function_definition))
{
	update_node_list();
}

member_declaration_function_definition::member_declaration_function_definition(const member_declaration_function_definition& o):
	composite_node(),
    function_definition_(o.function_definition_)
{
	update_node_list();
}

member_declaration_function_definition::member_declaration_function_definition(member_declaration_function_definition&& o):
    function_definition_(std::move(o.function_definition_))
{
	update_node_list();
}

const member_declaration_function_definition&
member_declaration_function_definition::operator=(const member_declaration_function_definition& o)
{
    function_definition_ = o.function_definition_;
	update_node_list();

	return *this;
}

void
member_declaration_function_definition::update_node_list()
{
	clear();
	add(function_definition_);
}

}}} //namespace socoa::cpp::syntax_tree
