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

#ifndef SOCOA_CPP_PROGRAM_TREE_NAMESPACE_MEMBER_IMPL_H
#define SOCOA_CPP_PROGRAM_TREE_NAMESPACE_MEMBER_IMPL_H

#include <memory>

namespace socoa { namespace cpp { namespace program_tree
{

class namespace_;

class namespace_member_impl
{
    public:
        bool
        has_parent() const;

        std::shared_ptr<namespace_>
        get_parent();

        const std::shared_ptr<namespace_>
        get_parent() const;

        void
        set_parent(std::shared_ptr<namespace_> parent);

    private:
        std::weak_ptr<namespace_> parent_;
};

}}} //namespace socoa::cpp::program_tree

#endif
