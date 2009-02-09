/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

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

#ifndef SOCOA_CPP_PROGRAM_TREE_NAMESPACE_PARENT_H
#define SOCOA_CPP_PROGRAM_TREE_NAMESPACE_PARENT_H

#include "name_tree_composite.h"

namespace socoa { namespace cpp { namespace semantic_graph
{

struct namespace_enclosing_scope: virtual public name_tree_composite
{
    virtual
    ~namespace_enclosing_scope(){};

    const std::vector<std::shared_ptr<namespace_>>&
    get_specific_members() const
    {
        return get_namespaces();
    }

    virtual
    const std::vector<std::shared_ptr<namespace_>>&
    get_namespaces() const = 0;

    virtual
    void
    add(std::shared_ptr<namespace_> a_namespace) = 0;

    virtual
    bool
    is_global() const = 0;
};

}}} //namespace socoa::cpp::semantic_graph

#endif
