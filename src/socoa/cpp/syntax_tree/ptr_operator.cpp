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

#include "ptr_operator.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

ptr_operator::ptr_operator
(
	type a_type,
	bool leading_double_colon,
	boost::optional<nested_name_specifier> a_nested_name_specifier,
	boost::optional<cv_qualifier_seq> a_cv_qualifier_seq
):
	type_(a_type),
	leading_double_colon_(leading_double_colon),
	nested_name_specifier_(a_nested_name_specifier),
	cv_qualifier_seq_(a_cv_qualifier_seq)
{
}

}}} //namespace socoa::cpp::syntax_tree

