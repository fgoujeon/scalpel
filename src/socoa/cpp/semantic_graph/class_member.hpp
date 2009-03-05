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

#ifndef SOCOA_CPP_PROGRAM_TREE_CLASS_MEMBER_HPP
#define SOCOA_CPP_PROGRAM_TREE_CLASS_MEMBER_HPP

#include <memory>
#include "name_tree_component.hpp"

namespace socoa { namespace cpp { namespace semantic_graph
{

class class_;

struct class_member: public virtual name_tree_component
{
    virtual
    ~class_member(){};

    virtual
    bool
    has_enclosing_scope() const = 0;

    virtual
    void
    set_enclosing_scope(std::shared_ptr<class_> enclosing_scope) = 0;

    virtual
    const std::string&
    get_name() const = 0;
};

}}} //namespace socoa::cpp::semantic_graph

#endif
