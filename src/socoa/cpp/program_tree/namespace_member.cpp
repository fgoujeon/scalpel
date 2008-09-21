/*
Socoa - Source Code Analysis Library
Copyright © 2008  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include "program.h"

#include "namespace_member.h"

namespace socoa { namespace cpp { namespace program_tree
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

}}} //namespace socoa::cpp::program_tree
