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

#include "nested_identifier_or_template_id.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

nested_identifier_or_template_id::nested_identifier_or_template_id
(
    bool leading_double_colon,
    std::shared_ptr<nested_name_specifier> a_nested_name_specifier,
    std::shared_ptr<identifier_or_template_id> an_identifier_or_template_id
):
    leading_double_colon_(leading_double_colon),
    nested_name_specifier_(a_nested_name_specifier),
    identifier_or_template_id_(an_identifier_or_template_id)
{
    assert(an_identifier_or_template_id);
}

bool
nested_identifier_or_template_id::has_leading_double_colon() const
{
    return leading_double_colon_;
}

const std::shared_ptr<nested_name_specifier>
nested_identifier_or_template_id::get_nested_name_specifier() const
{
    return nested_name_specifier_;
}

const std::shared_ptr<identifier_or_template_id>
nested_identifier_or_template_id::get_identifier_or_template_id() const
{
    return identifier_or_template_id_;
}

}}} //namespace socoa::cpp::program_syntax_tree
