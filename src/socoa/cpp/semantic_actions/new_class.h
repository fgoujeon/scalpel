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

#ifndef SOCOA_CPP_NEW_CLASS_H
#define SOCOA_CPP_NEW_CLASS_H

#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include "../scope_cursor.h"
#include "../program_tree/class_.h"
#include "../program_tree/named_scope.h"

namespace socoa { namespace cpp
{

template <class IteratorT>
class new_class
{
    public:
        new_class(scope_cursor& a_scope_cursor);

        void
        operator()(const IteratorT* first, const IteratorT* last) const;

    private:
        scope_cursor& scope_cursor_;
};

template <class IteratorT>
new_class<IteratorT>::new_class(scope_cursor& a_scope_cursor):
    scope_cursor_(a_scope_cursor)
{
}

template <class IteratorT>
void
new_class<IteratorT>::operator()(const IteratorT* first, const IteratorT* last) const
{
    std::string class_name(first, last);

    //get the current scope (if it's a class_parent)
    std::shared_ptr<program_tree::class_parent> current_scope = std::dynamic_pointer_cast<program_tree::class_parent>
    (
        scope_cursor_.get_current_scope()
    );
    assert(current_scope);

    //try to get an already existing namespace with the same name
    typedef std::vector<std::shared_ptr<program_tree::class_>> class_vector;
    const class_vector& existing_classes = current_scope->get_classes();
    const class_vector::const_iterator same_namespace_it = std::find_if
    (
        existing_classes.begin(),
		existing_classes.end(),
        std::bind
        (
            &program_tree::class_::has_that_name,
            std::placeholders::_1,
            class_name
        )
    );

    //create the new namespace or get the existing one
    std::shared_ptr<program_tree::class_> new_class;
    if(same_namespace_it == existing_classes.end()) //if no similar namespace has been found
    {
        //create a namespace object
        new_class = std::make_shared<program_tree::class_>(class_name);
        //add the new namespace to the current namespace
        current_scope->add(new_class);
    }
    else
    {
        new_class = *same_namespace_it;
    }

    //tell the scope cursor that we will enter in the new namespace
    scope_cursor_.set_last_created_scope(new_class);
}

}} //namespace socoa::cpp

#endif
