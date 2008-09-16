/*
Socoa - Source Code Analysis Library
Copyright © 2008  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_PTR_OPERATOR_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_PTR_OPERATOR_H

#include <memory>

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class ptr_operator
{
    public:
        enum type
        {
            ASTERISK,
            AMPERSAND
        };

        ptr_operator
        (
            type a_type,
            bool leading_double_colon
            //std::shared_ptr<nested_name_specifier> a_nested_name_specifier,
            //std::shared_ptr<cv_qualifier_seq> a_cv_qualifier_seq
        );

        type
        get_type() const;

        bool
        has_leading_double_colon() const;

        //std::shared_ptr<nested_name_specifier> m_nested_name_specifier;

        //std::shared_ptr<cv_qualifier_seq> m_cv_qualifier_seq;

    private:
        type m_type;
        bool m_leading_double_colon;
        //std::shared_ptr<nested_name_specifier> m_nested_name_specifier;
        //std::shared_ptr<cv_qualifier_seq> m_cv_qualifier_seq;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
