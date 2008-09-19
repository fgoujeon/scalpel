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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_NESTED_NAME_SPECIFIER_TEMPLATE_ID_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_NESTED_NAME_SPECIFIER_TEMPLATE_ID_H

#include "nested_name_specifier_part.h"
#include "template_id.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class nested_name_specifier_template_id: public nested_name_specifier_part
{
    public:
        nested_name_specifier_template_id
        (
            bool template_keyword,
            template_id&& a_template_id
        );

        bool
        has_template_keyword() const;

        const template_id&
        get_template_id() const;

        SOCOA_CPP_DEFINE_VISITABLE()

    private:
        bool m_template_keyword;
        template_id m_template_id;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
