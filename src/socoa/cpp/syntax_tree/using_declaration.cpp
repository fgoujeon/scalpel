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

#include "using_declaration.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

using_declaration::using_declaration
(
    bool typename_keyword,
    bool leading_double_colon,
    boost::optional<nested_name_specifier>&& a_nested_name_specifier,
    unqualified_id&& an_unqualified_id
):
    typename_keyword_(typename_keyword),
    leading_double_colon_(leading_double_colon),
    //nested_name_specifier_(a_nested_name_specifier),
    unqualified_id_(an_unqualified_id)
{
	if(a_nested_name_specifier)
		nested_name_specifier_ = std::move(std::unique_ptr<nested_name_specifier>(new nested_name_specifier(std::move(*a_nested_name_specifier))));

	if(nested_name_specifier_) add(*nested_name_specifier_);
	add(unqualified_id_);
}

using_declaration::using_declaration(using_declaration&& o):
    typename_keyword_(std::move(o.typename_keyword_)),
    leading_double_colon_(std::move(o.leading_double_colon_)),
    nested_name_specifier_(std::move(o.nested_name_specifier_)),
    unqualified_id_(std::move(o.unqualified_id_))
{
}

}}} //namespace socoa::cpp::syntax_tree
