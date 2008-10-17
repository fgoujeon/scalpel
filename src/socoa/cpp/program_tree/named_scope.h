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

#ifndef SOCOA_CPP_PROGRAM_TREE_NAMED_SCOPE_H
#define SOCOA_CPP_PROGRAM_TREE_NAMED_SCOPE_H

#include <string>

namespace socoa { namespace cpp { namespace program_tree
{

class named_scope_member;

struct named_scope
{
    virtual
    ~named_scope(){};

    virtual
    const std::string&
    get_name() const = 0;

    virtual
    const std::string
    get_full_name() const = 0;

    virtual
    bool
    is_global() const = 0;

    virtual
    bool
    has_parent() const = 0;

    virtual
    std::shared_ptr<named_scope>
    get_parent() = 0;

    virtual
    const std::shared_ptr<named_scope>
    get_parent() const = 0;
};

}}} //namespace socoa::cpp::program_tree

#endif
