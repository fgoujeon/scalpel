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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_USING_DECLARATION_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_USING_DECLARATION_H

#include <memory>
#include "visitor.h"
#include "member_declaration.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class nested_name_specifier;
class unqualified_id;

class using_declaration: public member_declaration
{
    public:
        using_declaration
        (
            bool typename_keyword,
            bool leading_double_colon,
            std::shared_ptr<nested_name_specifier> a_nested_name_specifier,
            std::shared_ptr<unqualified_id> an_unqualified_id
        );

        bool
        has_typename_keyword() const;

        bool
        has_leading_double_colon() const;

        const std::shared_ptr<nested_name_specifier>
        get_nested_name_specifier() const;

        const std::shared_ptr<unqualified_id>
        get_unqualified_id() const;

        SOCOA_CPP_DEFINE_VISITABLE()

    private:
        bool typename_keyword_;
        bool leading_double_colon_;
        std::shared_ptr<nested_name_specifier> nested_name_specifier_;
        std::shared_ptr<unqualified_id> unqualified_id_;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
