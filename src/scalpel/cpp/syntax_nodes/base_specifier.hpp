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

#ifndef SCALPEL_CPP_SYNTAX_NODES_BASE_SPECIFIER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_BASE_SPECIFIER_HPP

#include "access_specifier.hpp"
#include "nested_identifier_or_template_id.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
base_specifier
	= nested_identifier_or_template_id
	| "virtual" >> !s >> !access_specifier >> !s >> nested_identifier_or_template_id
	| access_specifier >> !s >> !str_p("virtual") >> !s >> nested_identifier_or_template_id
;
\endverbatim
*/
typedef
	sequence_node
	<
		optional_node<predefined_text_node<str::virtual_>>,
		optional_node<space>,
		optional_node<access_specifier>,
		optional_node<space>,
		optional_node<predefined_text_node<str::virtual_>>,
		optional_node<space>,
		nested_identifier_or_template_id
	>
	base_specifier
;

inline
bool
has_virtual_keyword(const base_specifier& o)
{
	return get<0>(o) || get<4>(o);
}

inline
const optional_node<access_specifier>&
get_access_specifier(const base_specifier& o)
{
	return get<2>(o);
}

inline
const nested_identifier_or_template_id&
get_nested_identifier_or_template_id(const base_specifier& o)
{
	return get<6>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
