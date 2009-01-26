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

#include "name_lookup.h"

#include <algorithm>
#include <functional>
#include "program_tree/name_tree_composite.h"
#include "program_tree/class_.h"

namespace socoa { namespace cpp
{

using namespace program_tree;

const std::shared_ptr<name_tree_component>
find_unqualified_name(const std::shared_ptr<name_tree_component> current_scope, const std::string& name, bool recursive);


const std::shared_ptr<name_tree_component>
find_unqualified_name(const std::shared_ptr<name_tree_component> current_scope, const std::string& name)
{
    return find_unqualified_name(current_scope, name, true);
}

const std::shared_ptr<name_tree_component>
find_unqualified_name(const std::shared_ptr<name_tree_component> current_scope, const std::string& name, bool recursive)
{
    /*
    1. Current scope
    */
    {
        const std::vector<std::shared_ptr<name_tree_component>> members = current_scope->get_members();
        std::vector<std::shared_ptr<name_tree_component>>::const_iterator member_it = std::find_if
        (
            members.begin(),
            members.end(),
            std::bind
            (
                &name_tree_component::has_that_name,
                std::placeholders::_1,
                name
            )
        );

        if(member_it != members.end()) //a name has been found
        {
            return *member_it;
        }
    }


    /*
    2. Enclosing scopes (recursive call)
    */
    {
        if
        (
            recursive &&
            current_scope->has_enclosing_scope() //is there at least an enclosing scope?
        )
        {
            const std::shared_ptr<program_tree::name_tree_component> found_symbol = find_unqualified_name(current_scope->get_enclosing_scope(), name, true);
            if(found_symbol)
            {
                return found_symbol;
            }
        }
    }


    /*
    3. Base classes (non-recursive)
    */
    {
        const std::vector<base_specifier>& base_specifiers = current_scope->get_base_specifiers();
        for
        (
            std::vector<base_specifier>::const_iterator i = base_specifiers.begin();
            i != base_specifiers.end();
            ++i
        ) //for each base specifier (== for each base class)
        {
            const base_specifier& base_spec = *i;
            const std::shared_ptr<class_> base_class = base_spec.get_class();
            const std::shared_ptr<program_tree::name_tree_component> found_symbol = find_unqualified_name(base_class, name, false);
            if(found_symbol)
            {
                return found_symbol;
            }
        }
    }

    return std::shared_ptr<name_tree_component>();
}

}} //namespace socoa::cpp
