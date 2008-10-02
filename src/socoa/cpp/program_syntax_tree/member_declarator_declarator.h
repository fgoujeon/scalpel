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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_MEMBER_DECLARATOR_DECLARATOR_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_MEMBER_DECLARATOR_DECLARATOR_H

#include <memory>
#include "visitor.h"
#include "member_declarator.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class declarator;

class member_declarator_declarator: public member_declarator
{
    public:
        member_declarator_declarator
        (
            std::shared_ptr<declarator> a_declarator,
            bool pure_specifier
        );

        const std::shared_ptr<declarator>
        get_declarator() const;

        bool
        has_pure_specifier() const;

        SOCOA_CPP_DEFINE_VISITABLE()

    private:
        std::shared_ptr<declarator> declarator_;
        bool pure_specifier_;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
