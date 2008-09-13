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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_INIT_DECLARATOR_LIST_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_INIT_DECLARATOR_LIST_H

#include <vector>
#include <memory>

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class init_declarator;

class init_declarator_list
{
    public:
        const std::vector<std::shared_ptr<init_declarator>>
        get_init_declarators() const;

        void
        set_init_declarators(std::vector<std::shared_ptr<init_declarator>> init_declarators);

        void
        add(std::shared_ptr<init_declarator> an_init_declarator);

    private:
        std::vector<std::shared_ptr<init_declarator>> m_init_declarators;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
