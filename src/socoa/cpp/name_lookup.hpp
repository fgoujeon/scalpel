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

#ifndef SOCOA_CPP_NAME_LOOKUP_HPP
#define SOCOA_CPP_NAME_LOOKUP_HPP

#include <string>
#include "syntax_tree.hpp"
#include "semantic_graph.hpp"

namespace socoa { namespace cpp { namespace name_lookup
{

const semantic_graph::named_item*
find_unqualified_name(const semantic_graph::scope& current_scope, const std::string& name);

semantic_graph::scope*
find_scope
(
	semantic_graph::scope& current_scope,
	const syntax_tree::nested_name_specifier& nested_name_specifier
);

}}} //namespace socoa::cpp::name_lookup

#endif
