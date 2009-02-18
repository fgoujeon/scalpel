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

#include "base_specifier.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

base_specifier::base_specifier
(
    bool virtual_keyword,
    boost::optional<access_specifier> an_access_specifier,
    boost::optional<nested_identifier_or_template_id> a_nested_identifier_or_template_id
):
    virtual_keyword_(virtual_keyword),
    access_specifier_(an_access_specifier),
    nested_identifier_or_template_id_(a_nested_identifier_or_template_id)
{
}

}}} //namespace socoa::cpp::syntax_tree
