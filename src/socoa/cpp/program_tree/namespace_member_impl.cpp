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

#include "namespace_member_impl.h"

#include <cassert>

namespace socoa { namespace cpp { namespace program_tree
{

bool
namespace_member_impl::has_parent() const
{
    return !parent_.expired();
}

std::shared_ptr<namespace_>
namespace_member_impl::get_parent()
{
    return parent_.lock();
}

const std::shared_ptr<namespace_>
namespace_member_impl::get_parent() const
{
    return parent_.lock();
}

void
namespace_member_impl::set_parent(std::shared_ptr<namespace_> parent)
{
    assert(parent_.expired()); //assert that member doesn't have any parent yet
    parent_ = parent;
}

}}} //namespace socoa::cpp::program_tree
