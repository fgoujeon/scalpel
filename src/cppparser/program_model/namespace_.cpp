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

#include "class_.h"
#include "enum_.h"
#include "typedef_.h"

#include "namespace_.h"

namespace cppparser
{

namespace_::namespace_()
{
}

namespace_::namespace_(const std::string& name):
    m_name(name)
{
}

const std::string&
namespace_::name() const
{
    return m_name;
}

const std::list<namespace_item*>&
namespace_::items() const
{
    return m_items;
}

void
namespace_::add(namespace_& a_namespace)
{
    m_items.push_back(&a_namespace);
}

void
namespace_::add(class_& a_class)
{
    m_items.push_back(&a_class);
}

void
namespace_::add(enum_& an_enum)
{
    m_items.push_back(&an_enum);
}

void
namespace_::add(typedef_& a_typedef)
{
    m_items.push_back(&a_typedef);
}

}
