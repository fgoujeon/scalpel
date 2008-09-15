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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_FUNCTION_DIRECT_DECLARATOR_PART_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_FUNCTION_DIRECT_DECLARATOR_PART_H

#include "direct_declarator_part.h"
#include "parameter_declaration_clause.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class function_direct_declarator_part: public direct_declarator_part
{
    public:
        explicit function_direct_declarator_part
        (
            parameter_declaration_clause&& a_parameter_declaration_clause
        );

        const parameter_declaration_clause&
        get_parameter_declaration_clause() const;

        void
        accept(visitor& a_visitor) const
        {
            a_visitor.visit(*this);
        }

    private:
        parameter_declaration_clause m_parameter_declaration_clause;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
