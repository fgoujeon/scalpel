/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_NAME_LOOKUP_HPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_NAME_LOOKUP_HPP

#include <string>
#include "../../syntax_tree.hpp"
#include "../../semantic_graph.hpp"

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis { namespace name_lookup
{

const semantic_entities::named_entity*
find_unqualified_name(const semantic_entities::scope& current_scope, const std::string& name);

semantic_entities::scope*
find_scope
(
	semantic_entities::scope& current_scope,
	const syntax_nodes::nested_name_specifier& nested_name_specifier
);

semantic_entities::scope*
recursive_ascent_find_scope
(
	semantic_entities::scope& start_scope,
	const std::string& scope_name
);

semantic_entities::scope*
find_scope
(
	semantic_entities::scope& parent_scope,
	const std::string& scope_name
);

}}}}} //namespace scalpel::cpp::detail::semantic_analysis::name_lookup

#endif
