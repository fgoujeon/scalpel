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

#ifndef SOCOA_CPP_SYNTAX_TREE_BUILT_IN_TYPE_SPECIFIER_H
#define SOCOA_CPP_SYNTAX_TREE_BUILT_IN_TYPE_SPECIFIER_H

#include "../../util/string_enumeration.h"
#include "simple_type_specifier.h"
#include "visitor.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

extern const std::vector<std::string> built_in_type_specifier_string_list;
struct built_in_type_specifier: public util::string_enumeration<built_in_type_specifier_string_list>, public simple_type_specifier
{
    built_in_type_specifier(const std::string& value);

    SOCOA_CPP_DEFINE_VISITABLE()
};

}}} //namespace socoa::cpp::syntax_tree

#endif
