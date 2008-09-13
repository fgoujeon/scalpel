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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_DECLARATOR_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_DECLARATOR_H

#include <memory>

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class direct_declarator;

class declarator
{
    public:
        declarator
        (
            std::shared_ptr<direct_declarator> a_direct_declarator
        );

        /*const std::vector<std::shared_ptr<ptr_operator>>&
        get_ptr_operators() const;

        void
        add(std::shared_ptr<ptr_operator> a_ptr_operator);*/

        const std::shared_ptr<direct_declarator>
        get_direct_declarator() const;

    private:
        //std::vector<std::shared_ptr<ptr_operator>> m_ptr_operators;
        std::shared_ptr<direct_declarator> m_direct_declarator;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
