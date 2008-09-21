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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_NESTED_NAME_SPECIFIER_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_NESTED_NAME_SPECIFIER_H

#include <vector>
#include <memory>

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class identifier_or_template_id;
class nested_name_specifier_part;

class nested_name_specifier
{
    public:
        nested_name_specifier
        (
            std::shared_ptr<identifier_or_template_id> an_identifier_or_template_id,
            std::vector<std::shared_ptr<nested_name_specifier_part>>&& a_nested_name_specifier_part
        );

        const std::shared_ptr<identifier_or_template_id>
        get_identifier_or_template_id() const;

        const std::vector<std::shared_ptr<nested_name_specifier_part>>&
        get_other_parts() const;

    private:
        std::shared_ptr<identifier_or_template_id> m_identifier_or_template_id;
        std::vector<std::shared_ptr<nested_name_specifier_part>> m_nested_name_specifier_part;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
