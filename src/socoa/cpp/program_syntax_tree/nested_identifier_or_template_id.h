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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_NESTED_IDENTIFIER_OR_TEMPLATE_ID_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_NESTED_IDENTIFIER_OR_TEMPLATE_ID_H

#include <memory>
#include <cassert>
#include "visitor.h"
#include "declarator_id.h"
#include "simple_type_specifier.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class nested_name_specifier;
class identifier_or_template_id;

class nested_identifier_or_template_id: public declarator_id, public simple_type_specifier
{
    public:
        nested_identifier_or_template_id
        (
            bool leading_double_colon,
            std::shared_ptr<nested_name_specifier> a_nested_name_specifier,
            std::shared_ptr<identifier_or_template_id> an_identifier_or_template_id
        );

        bool
        has_leading_double_colon() const;

        const std::shared_ptr<nested_name_specifier>
        get_nested_name_specifier() const;

        const std::shared_ptr<identifier_or_template_id>
        get_identifier_or_template_id() const;

        SOCOA_CPP_DEFINE_VISITABLE()

    private:
        bool leading_double_colon_;
        std::shared_ptr<nested_name_specifier> nested_name_specifier_;
        std::shared_ptr<identifier_or_template_id> identifier_or_template_id_;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
