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

#include <iostream>
#include "scope_cursor.h"

namespace cppparser
{

scope_cursor::scope_cursor():
    m_current_namespace(m_program_model.global_namespace())
{
}

program_model::program&
scope_cursor::program_model()
{
    return m_program_model;
}

std::weak_ptr<program_model::namespace_>
scope_cursor::current_namespace()
{
    return m_current_namespace;
}

void
scope_cursor::enter_namespace(std::weak_ptr<program_model::namespace_> a_namespace)
{
    m_current_namespace = a_namespace;
    std::cout << "entering in namespace: " << m_current_namespace.lock()->full_name() << std::endl;
}

void
scope_cursor::leave_current_namespace()
{
    m_current_namespace = m_current_namespace.lock()->parent();
    std::cout << "leaving namespace to: " << m_current_namespace.lock()->full_name() << std::endl;
}

} //namespace cppparser
