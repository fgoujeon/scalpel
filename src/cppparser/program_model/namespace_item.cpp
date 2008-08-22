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
#include "program.h"

#include "namespace_item.h"

namespace cppparser { namespace program_model
{

namespace_item::~namespace_item()
{
}

bool
namespace_item::has_parent() const
{
    return !m_parent.expired();
}

std::weak_ptr<namespace_>
namespace_item::parent()
{
    return m_parent;
}

const std::weak_ptr<namespace_>
namespace_item::parent() const
{
    return m_parent;
}

void
namespace_item::parent(std::weak_ptr<namespace_> parent)
{
    m_parent = parent;
}

}} //namespace cppparser::program_model
