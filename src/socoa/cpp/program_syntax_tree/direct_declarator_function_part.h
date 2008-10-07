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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_DIRECT_DECLARATOR_FUNCTION_PART_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_DIRECT_DECLARATOR_FUNCTION_PART_H

#include "visitor.h"
#include "direct_declarator_part.h"
#include "parameter_declaration_clause.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

struct direct_declarator_function_part: public direct_declarator_part
{
    explicit direct_declarator_function_part
    (
        parameter_declaration_clause&& a_parameter_declaration_clause
    );

    SOCOA_CPP_DEFINE_VISITABLE()

    const parameter_declaration_clause parameter_declaration_clause_;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
