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

#include "direct_declarator.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

direct_declarator::direct_declarator
(
    boost::optional<declarator_id> a_declarator_id,
    boost::optional<declarator> a_declarator,
    std::vector<other_part>&& other_parts
):
    declarator_id_(a_declarator_id),
    declarator_(a_declarator),
    other_parts_(other_parts)
{
}

direct_declarator::function_part::function_part
(
    parameter_declaration_clause&& a_parameter_declaration_clause,
    boost::optional<util::sequence<cv_qualifier>> a_cv_qualifier_seq
):
    parameter_declaration_clause_(a_parameter_declaration_clause),
    cv_qualifier_seq_(a_cv_qualifier_seq)
{
}

}}} //namespace socoa::cpp::syntax_tree
