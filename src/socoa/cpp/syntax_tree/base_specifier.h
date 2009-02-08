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

#ifndef SOCOA_CPP_SYNTAX_TREE_BASE_SPECIFIER_H
#define SOCOA_CPP_SYNTAX_TREE_BASE_SPECIFIER_H

#include <memory>
#include "access_specifier.h"
#include "nested_identifier_or_template_id.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

class base_specifier
{
    public:
        base_specifier
        (
            bool virtual_keyword,
            std::shared_ptr<access_specifier> an_access_specifier,
            std::shared_ptr<nested_identifier_or_template_id> a_nested_identifier_or_template_id
        );

        inline
        bool
        has_virtual_keyword() const;

        inline
        const std::shared_ptr<const access_specifier>
        get_access_specifier() const;

        inline
        const std::shared_ptr<const nested_identifier_or_template_id>
        get_nested_identifier_or_template_id() const;

    private:
        bool virtual_keyword_;
        std::shared_ptr<access_specifier> access_specifier_;
        std::shared_ptr<nested_identifier_or_template_id> nested_identifier_or_template_id_;
};

inline
bool
base_specifier::has_virtual_keyword() const
{
    return virtual_keyword_;
}

inline
const std::shared_ptr<const access_specifier>
base_specifier::get_access_specifier() const
{
    return access_specifier_;
}

inline
const std::shared_ptr<const nested_identifier_or_template_id>
base_specifier::get_nested_identifier_or_template_id() const
{
    return nested_identifier_or_template_id_;
}

}}} //namespace socoa::cpp::syntax_tree

#endif
