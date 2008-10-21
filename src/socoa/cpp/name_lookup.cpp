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

#include "name_lookup.h"

#include <algorithm>
#include <functional>
#include "program_tree/name_tree_composite.h"

namespace socoa { namespace cpp
{

using namespace program_tree;

const std::shared_ptr<name_tree_component>
find_unqualified_name(const std::shared_ptr<name_tree_component> current_scope, const std::string& name)
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
        if(current_scope->has_enclosing_scope()) //is there at least an enclosing scope?
        {
            const std::shared_ptr<program_tree::name_tree_component> found_symbol = find_unqualified_name(current_scope->get_enclosing_scope(), name);
            if(found_symbol)
            {
                return found_symbol;
            }
        }
    }

    return std::shared_ptr<name_tree_component>();
}

}} //namespace socoa::cpp
