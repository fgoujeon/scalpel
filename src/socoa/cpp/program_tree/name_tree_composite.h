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

#ifndef SOCOA_CPP_PROGRAM_TREE_NAME_TREE_COMPOSITE_H
#define SOCOA_CPP_PROGRAM_TREE_NAME_TREE_COMPOSITE_H

#include <vector>
#include "name_tree_component.h"

namespace socoa { namespace cpp { namespace program_tree
{

struct name_tree_composite: public virtual name_tree_component
{
    virtual
    ~name_tree_composite(){};

    virtual
    bool
    is_global() const = 0;

    virtual
    const std::vector<std::shared_ptr<name_tree_component>> &
    get_members() const = 0;
};

}}} //namespace socoa::cpp::program_tree

#endif
