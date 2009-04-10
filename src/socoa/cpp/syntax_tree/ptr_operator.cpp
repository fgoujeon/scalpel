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
	boost::optional<nested_name_specifier>&& a_nested_name_specifier,
	boost::optional<cv_qualifier_seq>&& a_cv_qualifier_seq
):
	type_(a_type),
	leading_double_colon_(leading_double_colon)/*,
	nested_name_specifier_(a_nested_name_specifier),
	cv_qualifier_seq_(a_cv_qualifier_seq)*/
{
	if(a_nested_name_specifier)
		nested_name_specifier_ = std::move(std::unique_ptr<nested_name_specifier>(new nested_name_specifier(std::move(*a_nested_name_specifier))));
	if(a_cv_qualifier_seq)
		cv_qualifier_seq_ = std::move(std::unique_ptr<cv_qualifier_seq>(new cv_qualifier_seq(std::move(*a_cv_qualifier_seq))));

	if(nested_name_specifier_) add(*nested_name_specifier_);
	if(cv_qualifier_seq_) add(*cv_qualifier_seq_);
}

ptr_operator::ptr_operator(ptr_operator&& o):
	type_(std::move(o.type_)),
	leading_double_colon_(std::move(o.leading_double_colon_)),
	nested_name_specifier_(std::move(o.nested_name_specifier_)),
	cv_qualifier_seq_(std::move(o.cv_qualifier_seq_))
{
}

}}} //namespace socoa::cpp::syntax_tree

