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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_PARAMETER_DECLARATION_CLAUSE_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_PARAMETER_DECLARATION_CLAUSE_H

#include <memory>

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class parameter_declaration_list;

class parameter_declaration_clause
{
    public:
        parameter_declaration_clause
        (
            std::shared_ptr<parameter_declaration_list> a_parameter_declaration_list,
            bool trailing_comma,
            bool ellipsis
        );

        const std::shared_ptr<parameter_declaration_list>
        get_parameter_declaration_list() const;

        bool
        has_trailing_comma() const;

        bool
        has_ellipsis() const;

    private:
        std::shared_ptr<parameter_declaration_list> m_parameter_declaration_list;
        bool m_trailing_comma;
        bool m_ellipsis;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
