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

#include "class_specifier.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

class_specifier::class_specifier
(
    class_head&& head,
    boost::optional<member_specification> a_member_specification
):
    class_head_(head),
    member_specification_(a_member_specification)
{
}

}}} //namespace socoa::cpp::syntax_tree
