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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_QUALIFIED_NESTED_ID_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_QUALIFIED_NESTED_ID_H

#include <memory>
#include "visitor.h"
#include "qualified_id.h"
#include "nested_name_specifier.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class unqualified_id;

struct qualified_nested_id: public qualified_id
{
    qualified_nested_id
    (
        bool leading_double_colon,
        nested_name_specifier&& a_nested_name_specifier,
        bool template_keyword,
        std::shared_ptr<unqualified_id> a_unqualified_id
    );

    SOCOA_CPP_DEFINE_VISITABLE()

    const bool leading_double_colon_;
    const nested_name_specifier nested_name_specifier_;
    const bool template_keyword_;
    const std::shared_ptr<unqualified_id> unqualified_id_;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
