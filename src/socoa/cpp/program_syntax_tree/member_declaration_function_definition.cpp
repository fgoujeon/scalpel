/*
Socoa - Source Code Analysis Library
Copyright © 2008  Florian Goujeon

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

#include "member_declaration_function_definition.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

member_declaration_function_definition::member_declaration_function_definition
(
    function_definition&& a_function_definition
):
    function_definition_(a_function_definition)
{
}

const function_definition&
member_declaration_function_definition::get_function_definition() const
{
    return function_definition_;
}

}}} //namespace socoa::cpp::program_syntax_tree
