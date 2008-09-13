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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_MEMBER_SPECIFICATION_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_MEMBER_SPECIFICATION_H

#include <vector>
#include <memory>
#include "visitable.h"
#include "member_specification_item.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class member_specification
{
    public:
        const std::vector<std::shared_ptr<member_specification_item>>&
        items() const;

        void
        add(std::shared_ptr<member_specification_item> visitable);

    private:
        std::vector<std::shared_ptr<member_specification_item>> m_items;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
