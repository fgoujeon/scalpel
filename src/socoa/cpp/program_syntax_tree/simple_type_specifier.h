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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_SIMPLE_TYPE_SPECIFIER_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_SIMPLE_TYPE_SPECIFIER_H

#include <string>
#include "type_specifier.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class simple_type_specifier: public type_specifier
{
    public:
        simple_type_specifier(const std::string& type);

        const std::string&
        type() const;

        void
        accept(visitor& a_visitor) const;

    private:
        std::string m_type;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
