/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_SYNTAX_NODES_QUALIFIED_NESTED_ID_HPP
#define SCALPEL_CPP_SYNTAX_NODES_QUALIFIED_NESTED_ID_HPP

#include "nested_name_specifier.hpp"
#include "unqualified_id.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
qualified_nested_id
	= ["::"], nested_name_specifier, ["template"], unqualified_id
;
\endverbatim
*/
typedef
	sequence_node
	<
		optional_node<predefined_text_node<str::double_colon>>,
		nested_name_specifier,
		optional_node<predefined_text_node<str::template_>>,
		unqualified_id
	>
	qualified_nested_id
;

inline
bool
has_leading_double_colon(const qualified_nested_id& o)
{
	return get<0>(o);
}

inline
const nested_name_specifier&
get_nested_name_specifier(const qualified_nested_id& o)
{
	return get<1>(o);
}

inline
bool
has_template_keyword(const qualified_nested_id& o)
{
	return get<2>(o);
}

inline
const unqualified_id&
get_unqualified_id(const qualified_nested_id& o)
{
	return get<3>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif

