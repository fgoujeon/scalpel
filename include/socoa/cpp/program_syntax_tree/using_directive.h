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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_USING_DIRECTIVE_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_USING_DIRECTIVE_H

#include <memory>
#include "visitor.h"
#include "block_declaration.h"
#include "identifier.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class nested_name_specifier;

struct using_directive: public block_declaration
{
    using_directive
    (
        bool leading_double_colon,
        std::shared_ptr<nested_name_specifier> a_nested_name_specifier,
        identifier&& an_identifier
    );

    SOCOA_CPP_DEFINE_VISITABLE()

    const bool leading_double_colon_;
    const std::shared_ptr<nested_name_specifier> nested_name_specifier_;
    const identifier identifier_;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
