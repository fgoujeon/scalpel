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

#ifndef SOCOA_CPP_SYNTAX_TREE_SIMPLE_DECLARATION_H
#define SOCOA_CPP_SYNTAX_TREE_SIMPLE_DECLARATION_H

#include <memory>
#include "visitor.h"
#include "block_declaration.h"
#include "../../util/sequence.h"
#include "../../util/extern_strings.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

class init_declarator;
class decl_specifier;

struct simple_declaration: public block_declaration
{
    simple_declaration
    (
        std::shared_ptr<util::sequence<decl_specifier>> a_decl_specifier_seq,
        std::shared_ptr<util::sequence<init_declarator, util::extern_strings::comma>> an_init_declarator_list
    );

    SOCOA_CPP_DEFINE_VISITABLE()

    const std::shared_ptr<util::sequence<decl_specifier>> decl_specifier_seq_;
    const std::shared_ptr<util::sequence<init_declarator, util::extern_strings::comma>> init_declarator_list_;
};

}}} //namespace socoa::cpp::syntax_tree

#endif
