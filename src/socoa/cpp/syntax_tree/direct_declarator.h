/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

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

#ifndef SOCOA_CPP_SYNTAX_TREE_DIRECT_DECLARATOR_H
#define SOCOA_CPP_SYNTAX_TREE_DIRECT_DECLARATOR_H

#include <vector>
#include <memory>

namespace socoa { namespace cpp { namespace syntax_tree
{

class declarator_id;
class declarator;
class direct_declarator_part;

class direct_declarator
{
    public:
        direct_declarator
        (
            std::shared_ptr<declarator_id> a_declarator_id,
            std::shared_ptr<declarator> a_declarator,
            std::vector<std::shared_ptr<direct_declarator_part>> other_parts
        );

        inline
        const std::shared_ptr<const declarator_id>
        get_declarator_id() const;

        inline
        const std::shared_ptr<const declarator>
        get_declarator() const;

        inline
        const std::vector<std::shared_ptr<direct_declarator_part>>
        get_other_parts() const;

    private:
        std::shared_ptr<declarator_id> declarator_id_;
        std::shared_ptr<declarator> declarator_;
        std::vector<std::shared_ptr<direct_declarator_part>> other_parts_;
};

inline
const std::shared_ptr<const declarator_id>
direct_declarator::get_declarator_id() const
{
    return declarator_id_;
}

inline
const std::shared_ptr<const declarator>
direct_declarator::get_declarator() const
{
    return declarator_;
}

inline
const std::vector<std::shared_ptr<direct_declarator_part>>
direct_declarator::get_other_parts() const
{
    return other_parts_;
}

}}} //namespace socoa::cpp::syntax_tree

#endif
