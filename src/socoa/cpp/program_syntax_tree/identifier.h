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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_IDENTIFIER_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_IDENTIFIER_H

#include <string>
#include "visitor.h"
#include "unqualified_id.h"
#include "nested_name_specifier_part.h"
#include "identifier_or_template_id.h"
#include "mem_initializer_id.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

struct identifier:
    public unqualified_id,
    public nested_name_specifier_part,
    public identifier_or_template_id,
    public mem_initializer_id
{
    explicit identifier(std::string&& value);

    SOCOA_CPP_DEFINE_VISITABLE()

    const std::string value_;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
