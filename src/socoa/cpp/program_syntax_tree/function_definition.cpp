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

#include "function_definition.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

function_definition::function_definition
(
    std::shared_ptr<util::sequence<decl_specifier>> a_decl_specifier_seq,
    declarator&& a_declarator,
    std::shared_ptr<ctor_initializer> a_ctor_initializer
):
    decl_specifier_seq_(a_decl_specifier_seq),
    declarator_(a_declarator),
    ctor_initializer_(a_ctor_initializer)
{
}

}}} //namespace socoa::cpp::program_syntax_tree
