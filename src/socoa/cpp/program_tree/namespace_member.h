/*
Socoa - Source Code Analysis Library
Copyright © 2008  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_PROGRAM_TREE_NAMESPACE_MEMBER_H
#define SOCOA_CPP_PROGRAM_TREE_NAMESPACE_MEMBER_H

#include <memory>

namespace socoa { namespace cpp { namespace program_tree
{

class namespace_;

class namespace_member
{
    public:
        virtual ~namespace_member();

        bool
        has_parent() const;

        std::shared_ptr<namespace_>
        parent();

        const std::shared_ptr<namespace_>
        parent() const;

        void
        parent(std::shared_ptr<namespace_> parent);

    private:
        std::weak_ptr<namespace_> m_parent;
};

}}} //namespace socoa::cpp::program_tree

#endif
