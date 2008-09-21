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

#include "class_specifier.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class_specifier::class_specifier
(
    class_head&& head,
    std::shared_ptr<member_specification> a_member_specification
):
    head_(head),
    member_specification_(a_member_specification)
{
}

const class_head&
class_specifier::get_head() const
{
    return head_;
}

const std::shared_ptr<member_specification>
class_specifier::get_member_specification() const
{
    return member_specification_;
}

}}} //namespace socoa::cpp::program_syntax_tree
