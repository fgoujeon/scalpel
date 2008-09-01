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

#include "namespace_member.h"

namespace cppparser { namespace program_tree
{

namespace_member::~namespace_member()
{
}

bool
namespace_member::has_parent() const
{
    return !m_parent.expired();
}

std::shared_ptr<namespace_>
namespace_member::parent()
{
    return m_parent.lock();
}

const std::shared_ptr<namespace_>
namespace_member::parent() const
{
    return m_parent.lock();
}

void
namespace_member::parent(std::shared_ptr<namespace_> parent)
{
    m_parent = parent;
}

}} //namespace cppparser::program_tree
