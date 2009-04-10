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

#include "parameter_declaration_clause.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

parameter_declaration_clause::parameter_declaration_clause
(
	boost::optional<parameter_declaration_list>&& a_parameter_declaration_list,
	bool trailing_comma,
	bool ellipsis
):
	parameter_declaration_list_(a_parameter_declaration_list),
	trailing_comma_(trailing_comma),
	ellipsis_(ellipsis)
{
	if(parameter_declaration_list_) add(*parameter_declaration_list_);
}

parameter_declaration_clause::parameter_declaration_clause(parameter_declaration_clause&& o):
	parameter_declaration_list_(std::move(o.parameter_declaration_list_)),
	trailing_comma_(o.trailing_comma_),
	ellipsis_(o.ellipsis_)
{
}

}}} //namespace socoa::cpp::syntax_tree
