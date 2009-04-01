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

#include "name_lookup.hpp"

#include <algorithm>
#include <functional>

namespace socoa { namespace cpp { namespace name_lookup
{

using namespace semantic_graph;

const named_item*
find_unqualified_name(const scope& current_scope, const std::string& name, bool recursive);


const named_item*
find_unqualified_name(const scope& current_scope, const std::string& name)
{
    return find_unqualified_name(current_scope, name, true);
}

const named_item*
find_unqualified_name(const scope& current_scope, const std::string& name, bool recursive)
{
    /*
    1. Current scope
    */
    {
		scope::named_item_const_iterator_range members = current_scope.get_named_items();
		scope::named_item_const_indirect_iterator member_it = std::find_if
        (
            members.begin(),
            members.end(),
            std::bind
            (
                &named_item::has_that_name,
                std::placeholders::_1,
                name
            )
        );
        if(member_it != members.end()) //if a name has been found
        {
            return &*member_it;
        }
    }


    /*
    2. Enclosing scopes (recursive call)
    */
    {
        if
        (
            recursive &&
            current_scope.has_enclosing_scope() //is there at least an enclosing scope?
        )
        {
            const semantic_graph::named_item* found_symbol = find_unqualified_name(current_scope.get_enclosing_scope(), name, true);
            if(found_symbol)
            {
                return found_symbol;
            }
        }
    }


//    /*
//    3. Base classes (non-recursive)
//    */
//    {
//        const std::list<base_specifier>& base_specifiers = current_scope->get_base_specifiers();
//        for
//        (
//            std::list<base_specifier>::const_iterator i = base_specifiers.begin();
//            i != base_specifiers.end();
//            ++i
//        ) //for each base specifier (== for each base class)
//        {
//            const base_specifier& base_spec = *i;
//            const std::shared_ptr<class_> base_class = base_spec.get_class();
//            const std::shared_ptr<semantic_graph::named_item> found_symbol = find_unqualified_name(base_class, name, false);
//            if(found_symbol)
//            {
//                return found_symbol;
//            }
//        }
//    }

	//no name has been found, we return a null pointer
    return 0;
}

}}} //namespace socoa::cpp::name_lookup

