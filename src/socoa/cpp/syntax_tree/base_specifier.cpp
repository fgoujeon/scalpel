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

#include "base_specifier.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

base_specifier::base_specifier
(
    bool virtual_keyword,
//    boost::optional<access_specifier>&& an_access_specifier,
    boost::optional<nested_identifier_or_template_id>&& a_nested_identifier_or_template_id
):
    virtual_keyword_(virtual_keyword)/*,
    access_specifier_(an_access_specifier),
    nested_identifier_or_template_id_(a_nested_identifier_or_template_id)*/
{
	/*
	if(an_access_specifier)
		access_specifier_ = std::move(std::unique_ptr<access_specifier>(new access_specifier(std::move(*an_access_specifier))));
		*/
	if(a_nested_identifier_or_template_id)
		nested_identifier_or_template_id_ = std::move(std::unique_ptr<nested_identifier_or_template_id>(new nested_identifier_or_template_id(std::move(*a_nested_identifier_or_template_id))));

	if(access_specifier_) add(*access_specifier_);
	if(nested_identifier_or_template_id_) add(*nested_identifier_or_template_id_);
}

base_specifier::base_specifier(base_specifier&& o):
    virtual_keyword_(std::move(o.virtual_keyword_)),
    access_specifier_(std::move(o.access_specifier_)),
    nested_identifier_or_template_id_(std::move(o.nested_identifier_or_template_id_))
{
}

}}} //namespace socoa::cpp::syntax_tree
