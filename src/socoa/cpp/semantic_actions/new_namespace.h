/*
CppParser - Standard C++ programming language parsing library
Copyright © 2008  Florian Goujeon

This file is part of CppParser.

CppParser is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

CppParser is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with CppParser.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_NEW_NAMESPACE_H
#define SOCOA_CPP_NEW_NAMESPACE_H

#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include "../scope_cursor.h"
#include "../program_tree/namespace_.h"
#include "../program_tree/named_scope.h"

namespace socoa { namespace cpp
{

template <class IteratorT>
class new_namespace
{
    public:
        new_namespace(scope_cursor& a_scope_cursor);

        void
        operator()(const IteratorT* first, const IteratorT* last) const;

    private:
        scope_cursor& scope_cursor_;
};

template <class IteratorT>
new_namespace<IteratorT>::new_namespace(scope_cursor& a_scope_cursor):
    scope_cursor_(a_scope_cursor)
{
}

template <class IteratorT>
void
new_namespace<IteratorT>::operator()(const IteratorT* first, const IteratorT* last) const
{
    std::string namespace_name(first, last);

    //get the current scope (if it's a namespace_parent)
    std::shared_ptr<program_tree::namespace_parent> current_scope = std::dynamic_pointer_cast<program_tree::namespace_parent>
    (
        scope_cursor_.get_current_scope()
    );
    assert(current_scope);

    //try to get an already existing namespace with the same name
    typedef std::vector<std::shared_ptr<program_tree::namespace_>> namespace_vector;
    const namespace_vector& existing_namespaces = current_scope->get_namespaces();
    const namespace_vector::const_iterator same_namespace_it = std::find_if
    (
        existing_namespaces.begin(),
		existing_namespaces.end(),
        std::bind
        (
            &program_tree::namespace_::has_that_name,
            std::placeholders::_1,
            namespace_name
        )
    );

    //create the new namespace or get the existing one
    std::shared_ptr<program_tree::namespace_> new_namespace;
    if(same_namespace_it == existing_namespaces.end()) //if no similar namespace has been found
    {
        //create a namespace object
        new_namespace = std::make_shared<program_tree::namespace_>(namespace_name);
        //add the new namespace to the current namespace
        current_scope->add(new_namespace);
    }
    else
    {
        new_namespace = *same_namespace_it;
    }

    //tell the scope cursor that we will enter in the new namespace
    scope_cursor_.set_last_created_scope(new_namespace);
}

}} //namespace socoa::cpp

#endif
