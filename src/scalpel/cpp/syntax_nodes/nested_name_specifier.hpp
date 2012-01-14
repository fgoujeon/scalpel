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

#ifndef SCALPEL_CPP_SYNTAX_NODES_NESTED_NAME_SPECIFIER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_NESTED_NAME_SPECIFIER_HPP

#include "identifier_or_template_id.hpp"
#include "common.hpp"

#include "detail/macros/sequence_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef
	sequence_node
	<
		optional_node<predefined_text_node<str::template_>>,
		identifier_or_template_id,
		predefined_text_node<str::double_colon>
	>
	nested_name_specifier_last_part
;

inline
bool
has_template_keyword(const nested_name_specifier_last_part& o)
{
	return get<0>(o);
}

inline
const identifier_or_template_id&
get_identifier_or_template_id(const nested_name_specifier_last_part& o)
{
	return get<1>(o);
}



typedef
	list_node<nested_name_specifier_last_part>
	nested_name_specifier_last_part_seq
;

/**
nested_name_specifier
	= identifier_or_template_id >> !s >> "::" >> !(!s >> nested_name_specifier_last_part_seq)
;
nested_name_specifier_last_part_seq
	= nested_name_specifier_last_part % !s
;
nested_name_specifier_last_part
	= !(str_p("template") >> !s) >> identifier_or_template_id >> !s >> "::"
;
*/

SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	nested_name_specifier,
	(identifier_or_template_id)
	(predefined_text_node<str::double_colon>)
	(optional_node<nested_name_specifier_last_part_seq>)
)

inline
const identifier_or_template_id&
get_identifier_or_template_id(const nested_name_specifier& o)
{
	return get<0>(o);
}

inline
const optional_node<nested_name_specifier_last_part_seq>&
get_last_part_seq(const nested_name_specifier& o)
{
	return get<2>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_declaration_undef.hpp"

#endif

