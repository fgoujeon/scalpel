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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_SIMPLE_DECLARATION_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_SIMPLE_DECLARATION_H

#include <memory>
#include "declaration.h"
#include "decl_specifier_seq.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class init_declarator_list;

class simple_declaration: public declaration
{
    public:
        simple_declaration
        (
            std::shared_ptr<decl_specifier_seq> a_decl_specifier_seq,
            std::shared_ptr<init_declarator_list> an_init_declarator_list
        );

        const std::shared_ptr<decl_specifier_seq>
        get_decl_specifier_seq() const;

        const std::shared_ptr<init_declarator_list>
        get_init_declarator_list() const;

        SOCOA_CPP_DEFINE_VISITABLE()

    private:
        std::shared_ptr<decl_specifier_seq> m_decl_specifier_seq;
        std::shared_ptr<init_declarator_list> m_init_declarator_list;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
