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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_MEMBER_DECLARATION_MEMBER_DECLARATOR_LIST_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_MEMBER_DECLARATION_MEMBER_DECLARATOR_LIST_H

#include <memory>
#include "visitor.h"
#include "member_declaration.h"
#include "../../util/sequence.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class decl_specifier;
class member_declarator;

struct member_declaration_member_declarator_list: public member_declaration
{
    member_declaration_member_declarator_list
    (
        std::shared_ptr<util::sequence<decl_specifier>> a_decl_specifier_seq,
        std::shared_ptr<util::sequence<member_declarator, ','>> a_member_declarator_list
    );

    SOCOA_CPP_DEFINE_VISITABLE()

    const std::shared_ptr<util::sequence<decl_specifier>> decl_specifier_seq_;
    const std::shared_ptr<util::sequence<member_declarator, ','>> member_declarator_list_;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
