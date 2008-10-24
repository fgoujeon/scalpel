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

#ifndef SOCOA_CPP_SEMANTIC_ACTIONS_NEW_NAMED_SCOPE_H
#define SOCOA_CPP_SEMANTIC_ACTIONS_NEW_NAMED_SCOPE_H

#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include "../scope_cursor.h"

namespace socoa { namespace cpp { namespace semantic_actions
{

template <class IteratorT, class ScopeT>
class create_named_scope
{
    public:
        create_named_scope(scope_cursor& a_scope_cursor);

        void
        operator()(const IteratorT* first, const IteratorT* last) const;

    private:
        scope_cursor& scope_cursor_;
};

template <class IteratorT, class ScopeT>
create_named_scope<IteratorT, ScopeT>::create_named_scope(scope_cursor& a_scope_cursor):
    scope_cursor_(a_scope_cursor)
{
}

template <class IteratorT, class ScopeT>
void
create_named_scope<IteratorT, ScopeT>::operator()(const IteratorT* first, const IteratorT* last) const
{
    std::string scope_name(first, last);

    //get the current scope (if it's able to hold a ScopeT == if its type is ScopeT::enclosing_scope)
    std::shared_ptr<typename ScopeT::enclosing_scope> current_scope = std::dynamic_pointer_cast<typename ScopeT::enclosing_scope>
    (
        scope_cursor_.get_current_scope()
    );
    assert(current_scope); //should exist as grammar defined it

    //try to get an already existing named scope with the same name
    typedef std::vector<std::shared_ptr<ScopeT>> scope_vector_t;
    const scope_vector_t& existing_scopes = current_scope->get_specific_members();
    typename scope_vector_t::const_iterator same_scope_it = std::find_if
    (
        existing_scopes.begin(),
		existing_scopes.end(),
        std::bind
        (
            &ScopeT::has_that_name,
            std::placeholders::_1,
            scope_name
        )
    );

    //create the new scope or get the existing one
    std::shared_ptr<ScopeT> new_scope;
    if(same_scope_it == existing_scopes.end()) //if no similar scope has been found
    {
        //create a scope object
        new_scope = std::make_shared<ScopeT>(scope_name);
        //add the new scope to the current scope
        current_scope->add(new_scope);
    }
    else
    {
        new_scope = *same_scope_it;
    }

    //tell the scope cursor that we will enter in the new namespace
    scope_cursor_.set_last_encountered_scope_header_scope(new_scope);
}

}}} //namespace socoa::cpp::semantic_actions

#endif
