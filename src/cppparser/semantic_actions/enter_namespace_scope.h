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

#ifndef CPPPARSER_ENTER_NAMESPACE_SCOPE_H
#define CPPPARSER_ENTER_NAMESPACE_SCOPE_H

#include <string>
#include <iostream>
#include "../scope_cursor.h"
#include "../program_model/program.h"
#include "../program_model/namespace_.h"

namespace cppparser
{

template <class IteratorT>
class enter_namespace_scope
{
    public:
        enter_namespace_scope(scope_cursor& scope_cursor);
        void operator()(const IteratorT* first, const IteratorT* last) const;

    private:
        scope_cursor& m_scope_cursor;
};

template <class IteratorT>
enter_namespace_scope<IteratorT>::enter_namespace_scope(scope_cursor& scope_cursor):
    m_scope_cursor(scope_cursor)
{
}

template <class IteratorT>
void
enter_namespace_scope<IteratorT>::operator()(const IteratorT* first, const IteratorT* last) const
{
    std::string namespace_name(first, last);
    std::shared_ptr<program_model::namespace_> current_namespace = m_scope_cursor.current_namespace().lock();

    //get the namespace_ object representing the entered namespace
    std::shared_ptr<program_model::namespace_> entered_namespace = current_namespace->find_member<program_model::namespace_>(namespace_name);
    assert(entered_namespace && "that namespace doesn't exist");

    //make point the scope cursor to the entered namespace
    m_scope_cursor.enter_namespace(entered_namespace);
}

} //namespace cppparser

#endif
