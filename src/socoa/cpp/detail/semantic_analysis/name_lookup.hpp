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

#ifndef SOCOA_CPP_DETAIL_SEMANTIC_ANALYSIS_NAME_LOOKUP_HPP
#define SOCOA_CPP_DETAIL_SEMANTIC_ANALYSIS_NAME_LOOKUP_HPP

#include <string>
#include "../../syntax_tree.hpp"
#include "../../semantic_graph.hpp"

namespace socoa { namespace cpp { namespace detail { namespace semantic_analysis { namespace name_lookup
{

const semantic_nodes::named_entity*
find_unqualified_name(const semantic_nodes::scope& current_scope, const std::string& name);

semantic_nodes::scope*
find_scope
(
	semantic_nodes::scope& current_scope,
	const syntax_nodes::nested_name_specifier& nested_name_specifier
);

}}}}} //namespace socoa::cpp::detail::semantic_analysis::name_lookup

#endif
