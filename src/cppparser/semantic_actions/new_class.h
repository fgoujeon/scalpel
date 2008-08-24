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

#ifndef CPPPARSER_NEW_CLASS_H
#define CPPPARSER_NEW_CLASS_H

#include "../scope_cursor.h"
#include "../program_model/class_.h"

namespace cppparser
{

template <class IteratorT>
class new_class
{
    public:
        new_class(scope_cursor& scope_cursor);
        void operator()(const IteratorT* first, const IteratorT* last) const;

    private:
        scope_cursor& m_scope_cursor;
};

template <class IteratorT>
new_class<IteratorT>::new_class(scope_cursor& scope_cursor):
    m_scope_cursor(scope_cursor)
{
}

template <class IteratorT>
void
new_class<IteratorT>::operator()(const IteratorT* first, const IteratorT* last) const
{
    std::string class_name(first, last);
    std::shared_ptr<program_model::namespace_> current_namespace = m_scope_cursor.current_namespace().lock();

    //try to get an already existing class with the same name
    std::shared_ptr<program_model::class_> new_class = current_namespace->find_member_by_name<program_model::class_>(class_name);

    if(!new_class) //if the class is really a new one
    {
        //create a class object
        //new_class = std::make_shared<program_model::class_>(class_name);
        new_class = std::shared_ptr<program_model::class_>(new program_model::class_(class_name));
        //add the new class to the current namespace
        current_namespace->add(new_class);

        std::cout << "new class " << class_name << std::endl;
    }
}

} //namespace cppparser

#endif
