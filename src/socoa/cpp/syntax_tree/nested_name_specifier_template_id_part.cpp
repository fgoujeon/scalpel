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

#include "nested_name_specifier_template_id_part.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

nested_name_specifier_template_id_part::nested_name_specifier_template_id_part
(
    bool template_keyword,
    template_id&& a_template_id
):
    template_keyword_(template_keyword),
    template_id_(a_template_id)
{
}

}}} //namespace socoa::cpp::syntax_tree
