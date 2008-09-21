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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_FUNCTION_DEFINITION_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_FUNCTION_DEFINITION_H

#include <memory>
#include "declaration.h"
#include "declarator.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class decl_specifier_seq;

class function_definition: public declaration
{
    public:
        function_definition
        (
            std::shared_ptr<decl_specifier_seq> a_decl_specifier_seq,
            declarator&& a_declarator
        );

        const std::shared_ptr<decl_specifier_seq>
        get_decl_specifier_seq() const;

        const declarator&
        get_declarator() const;

        SOCOA_CPP_DEFINE_VISITABLE()

    private:
        std::shared_ptr<decl_specifier_seq> m_decl_specifier_seq;
        declarator m_declarator;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
