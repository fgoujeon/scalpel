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

#ifndef SOCOA_CPP_PROGRAM_TREE_CLASS_PARENT_H
#define SOCOA_CPP_PROGRAM_TREE_CLASS_PARENT_H

#include "named_scope.h"

namespace socoa { namespace cpp { namespace program_tree
{

class class_;

struct class_parent: virtual public named_scope
{
    virtual
    ~class_parent(){};

    const std::vector<std::shared_ptr<class_>>&
    get_specific_members() const
    {
        return get_classes();
    }

    virtual
    const std::vector<std::shared_ptr<class_>>&
    get_classes() const = 0;

    virtual
    void
    add(std::shared_ptr<class_> a_class) = 0;

    virtual
    bool
    is_global() const = 0;
};

}}} //namespace socoa::cpp::program_tree

#endif
