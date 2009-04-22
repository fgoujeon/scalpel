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

#ifndef SOCOA_CPP_SYNTAX_TREE_CV_QUALIFIER_HPP
#define SOCOA_CPP_SYNTAX_TREE_CV_QUALIFIER_HPP

#include "string_enumeration_node.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

extern const std::vector<std::string> cv_qualifier_string_list;
typedef string_enumeration_node<cv_qualifier_string_list> cv_qualifier;

}}} //namespace socoa::cpp::syntax_nodes

#endif
