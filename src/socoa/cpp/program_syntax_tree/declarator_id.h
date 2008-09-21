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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_DECLARATOR_ID_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_DECLARATOR_ID_H

#include <memory>

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class id_expression;

class declarator_id
{
    public:
        explicit declarator_id(std::shared_ptr<id_expression> an_id_expression);

        const std::shared_ptr<id_expression>
        get_id_expression() const;

    private:
        std::shared_ptr<id_expression> m_id_expression;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif