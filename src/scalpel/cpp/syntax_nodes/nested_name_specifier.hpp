/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef
	sequence_node
	<
		optional_node<predefined_text_node<str::template_>>,
		optional_node<space>,
		identifier_or_template_id,
		optional_node<space>,
		predefined_text_node<str::double_colon>
	>
	nested_name_specifier_last_part
;

inline
const identifier_or_template_id&
get_identifier_or_template_id(const nested_name_specifier_last_part& o)
{
	return get<2>(o);
}



typedef
	list_node<nested_name_specifier_last_part>
	nested_name_specifier_last_part_seq
;

typedef
	sequence_node
	<
		identifier_or_template_id,
		optional_node<space>,
		predefined_text_node<str::double_colon>,
		optional_node<space>,
		optional_node<nested_name_specifier_last_part_seq>
	>
	nested_name_specifier_t
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

struct nested_name_specifier: public nested_name_specifier_t
{
	nested_name_specifier
	(
		identifier_or_template_id&& o0,
		optional_node<space>&& o1,
		predefined_text_node<str::double_colon>&& o2,
		optional_node<space>&& o3,
		optional_node<nested_name_specifier_last_part_seq>&& o4
	):
		nested_name_specifier_t(o0, o1, o2, o3, o4)
	{
	}

	nested_name_specifier
	(
		head_node_t&& head,
		tail_sequence_node_t&& tail
	):
		nested_name_specifier_t(head, tail)
	{
	}

	nested_name_specifier(const nested_name_specifier& o):
		nested_name_specifier_t(o)
	{
	}

	nested_name_specifier(nested_name_specifier&& o):
		nested_name_specifier_t(o)
	{
	}
};

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
	return get<4>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
