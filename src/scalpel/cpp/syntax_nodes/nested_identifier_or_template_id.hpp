/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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

#ifndef SCALPEL_CPP_SYNTAX_NODES_NESTED_IDENTIFIER_OR_TEMPLATE_ID_HPP
#define SCALPEL_CPP_SYNTAX_NODES_NESTED_IDENTIFIER_OR_TEMPLATE_ID_HPP

#include "nested_name_specifier.hpp"
#include "identifier_or_template_id.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
nested_identifier_or_template_id
	= !(str_p("::") >> !s) >> !(nested_name_specifier >> !s) >> identifier_or_template_id
;
*/
typedef
	sequence_node
	<
		optional_node<predefined_text_node<str::double_colon>>,
		optional_node<nested_name_specifier>,
		identifier_or_template_id
	>
	nested_identifier_or_template_id
;

inline
bool
has_leading_double_colon(const nested_identifier_or_template_id& o)
{
	return get<0>(o);
}

inline
const optional_node<nested_name_specifier>&
get_nested_name_specifier(const nested_identifier_or_template_id& o)
{
	return get<1>(o);
}

inline
const identifier_or_template_id&
get_identifier_or_template_id(const nested_identifier_or_template_id& o)
{
	return get<2>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif

