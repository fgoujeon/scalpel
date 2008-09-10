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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_ACCESS_SPECIFIER_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_ACCESS_SPECIFIER_H

#include "member_specification_item.h"
#include "item.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class access_specifier: public member_specification_item, public item
{
    public:
        enum possible_value
        {
            PUBLIC,
            PROTECTED,
            PRIVATE
        };

        access_specifier(possible_value value);

        possible_value
        value() const;

        void
        accept(visitor& a_visitor) const;

    private:
        possible_value m_value;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
