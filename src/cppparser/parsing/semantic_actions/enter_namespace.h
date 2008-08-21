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

#ifndef CPPPARSER_PARSING_SEMANTIC_ACTIONS_ENTER_NAMESPACE_H
#define CPPPARSER_PARSING_SEMANTIC_ACTIONS_ENTER_NAMESPACE_H

#include <string>
#include <iostream>
#include "../cursor.h"
#include "../../program_model/program.h"
#include "../../program_model/namespace_.h"

namespace cppparser { namespace parsing { namespace semantic_actions
{

template <class IteratorT>
class enter_namespace
{
    public:
        enter_namespace(parsing::cursor& cursor);
        void operator()(const IteratorT* first, const IteratorT* last) const;

    private:
        parsing::cursor& m_cursor;
};

template <class IteratorT>
enter_namespace<IteratorT>::enter_namespace(parsing::cursor& cursor):
    m_cursor(cursor)
{
}

template <class IteratorT>
void
enter_namespace<IteratorT>::operator()(const IteratorT* first, const IteratorT* last) const
{
    //create a namespace and put cursor into it
    std::string str(first, last);
    std::shared_ptr<program_model::namespace_> new_namespace = std::make_shared<program_model::namespace_>(str);
    m_cursor.current_namespace().lock()->add(new_namespace);
    new_namespace->parent(m_cursor.current_namespace()); //TODO I'd like this operation to be handled by namespace_::add() function itself
    m_cursor.enter_namespace(new_namespace);
}

}}} //namespace cppparser::parsing::semantic_actions

#endif
