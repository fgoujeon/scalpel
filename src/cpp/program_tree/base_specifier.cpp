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

#include <socoa/cpp/program_tree/base_specifier.h>

namespace socoa { namespace cpp { namespace program_tree
{

base_specifier::base_specifier
(
    std::shared_ptr<class_> a_class,
    program_syntax_tree::access_specifier access_specifier,
    bool is_virtual
):
    base_class_(a_class),
    access_specifier_(access_specifier),
    virtual_(is_virtual)
{
}

}}} //namespace socoa::cpp::program_tree
