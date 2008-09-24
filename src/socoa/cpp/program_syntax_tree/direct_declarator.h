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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_DIRECT_DECLARATOR_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_DIRECT_DECLARATOR_H

#include <vector>
#include <memory>

namespace socoa { namespace cpp { namespace program_syntax_tree
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
            std::vector<std::shared_ptr<direct_declarator_part>>&& other_parts
        );

        const std::shared_ptr<declarator_id>
        get_declarator_id() const;

        const std::shared_ptr<declarator>
        get_declarator() const;

        const std::vector<std::shared_ptr<direct_declarator_part>>&
        get_other_parts() const;

    private:
        std::shared_ptr<declarator_id> m_declarator_id;
        std::shared_ptr<declarator> m_declarator;
        std::vector<std::shared_ptr<direct_declarator_part>> m_other_parts;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
