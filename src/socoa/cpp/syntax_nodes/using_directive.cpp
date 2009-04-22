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

#include "using_directive.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

using_directive::using_directive
(
    bool leading_double_colon,
    boost::optional<nested_name_specifier>&& a_nested_name_specifier,
    identifier&& an_identifier
):
    leading_double_colon_(leading_double_colon),
    nested_name_specifier_(a_nested_name_specifier),
    identifier_(std::move(an_identifier))
{
	update_node_list();
}

using_directive::using_directive(const using_directive& o):
	composite_node(),
    leading_double_colon_(o.leading_double_colon_),
    nested_name_specifier_(o.nested_name_specifier_),
    identifier_(o.identifier_)
{
	update_node_list();
}

using_directive::using_directive(using_directive&& o):
    leading_double_colon_(std::move(o.leading_double_colon_)),
    nested_name_specifier_(std::move(o.nested_name_specifier_)),
    identifier_(std::move(o.identifier_))
{
	update_node_list();
}

const using_directive&
using_directive::operator=(const using_directive& o)
{
    leading_double_colon_ = o.leading_double_colon_;
    nested_name_specifier_ = o.nested_name_specifier_;
    identifier_ = o.identifier_;
	update_node_list();

	return *this;
}

void
using_directive::update_node_list()
{
	clear();
	if(nested_name_specifier_) add(*nested_name_specifier_);
	add(identifier_);
}

}}} //namespace socoa::cpp::syntax_nodes

