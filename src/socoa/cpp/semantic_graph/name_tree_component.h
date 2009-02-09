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

#ifndef SOCOA_CPP_PROGRAM_TREE_NAME_TREE_COMPONENT_H
#define SOCOA_CPP_PROGRAM_TREE_NAME_TREE_COMPONENT_H

#include <string>
#include <memory>
#include <vector>

namespace socoa { namespace cpp { namespace semantic_graph
{

class name_tree_composite;
class base_specifier;

struct name_tree_component
{
    name_tree_component() = default;

    name_tree_component(const name_tree_component&) = delete;

    name_tree_component&
    operator=(const name_tree_component&) = delete;

    virtual
    ~name_tree_component(){};

    virtual
    const std::string&
    get_name() const = 0;

    virtual
    bool
    has_that_name(const std::string& name) const = 0;

    virtual
    const std::string
    get_full_name() const = 0;

    virtual
    bool
    is_a_type() const = 0;

    virtual
    bool
    has_enclosing_scope() const = 0;

    virtual
    std::shared_ptr<name_tree_composite>
    get_enclosing_scope() = 0;

    virtual
    const std::shared_ptr<name_tree_composite>
    get_enclosing_scope() const = 0;

    virtual
    const std::vector<std::shared_ptr<name_tree_component>>&
    get_members() const = 0;

    virtual
    const std::vector<base_specifier>&
    get_base_specifiers() const = 0;
};

}}} //namespace socoa::cpp::semantic_graph

#endif
