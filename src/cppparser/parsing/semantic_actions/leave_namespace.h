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

#ifndef CPPPARSER_PARSING_SEMANTIC_ACTIONS_LEAVE_NAMESPACE_H
#define CPPPARSER_PARSING_SEMANTIC_ACTIONS_LEAVE_NAMESPACE_H

#include <string>
#include <iostream>
#include "../cursor.h"
#include "../../program_model/program.h"
#include "../../program_model/namespace_.h"

namespace cppparser { namespace parsing { namespace semantic_actions
{

template <class IteratorT>
class leave_namespace
{
    public:
        leave_namespace(parsing::cursor& cursor);
        void operator()(const IteratorT* first, const IteratorT* last) const;

    private:
        parsing::cursor& m_cursor;
};

template <class IteratorT>
leave_namespace<IteratorT>::leave_namespace(parsing::cursor& cursor):
    m_cursor(cursor)
{
}

template <class IteratorT>
void
leave_namespace<IteratorT>::operator()(const IteratorT* first, const IteratorT* last) const
{
    m_cursor.leave_current_namespace();
}

}}} //namespace cppparser::parsing::semantic_actions

#endif
