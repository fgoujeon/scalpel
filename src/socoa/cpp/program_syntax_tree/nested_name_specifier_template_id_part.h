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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_NESTED_NAME_SPECIFIER_TEMPLATE_ID_PART_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_NESTED_NAME_SPECIFIER_TEMPLATE_ID_PART_H

#include "visitor.h"
#include "nested_name_specifier_part.h"
#include "template_id.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

struct nested_name_specifier_template_id_part: public nested_name_specifier_part
{
    nested_name_specifier_template_id_part
    (
        bool template_keyword,
        template_id&& a_template_id
    );

    SOCOA_CPP_DEFINE_VISITABLE()

    const bool template_keyword_;
    const template_id template_id_;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
