/*
CppParser - Standard C++ programming language parsing library
Copyright © 2008, 2009  Florian Goujeon

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

#ifndef SOCOA_CPP_SEMANTIC_ACTIONS_ENTER_SCOPE_H
#define SOCOA_CPP_SEMANTIC_ACTIONS_ENTER_SCOPE_H

#include "../scope_cursor.h"

namespace socoa { namespace cpp { namespace semantic_actions
{

template <class IteratorT>
class enter_scope
{
    public:
        enter_scope(scope_cursor& a_scope_cursor);

        void
        operator()(IteratorT, IteratorT) const;

    private:
        scope_cursor& scope_cursor_;
};

template <class IteratorT>
enter_scope<IteratorT>::enter_scope(scope_cursor& a_scope_cursor):
    scope_cursor_(a_scope_cursor)
{
}

template <class IteratorT>
void
enter_scope<IteratorT>::operator()(IteratorT, IteratorT) const
{
    scope_cursor_.enter_last_encountered_scope_header_scope();
}

}}} //namespace socoa::cpp::semantic_actions

#endif
