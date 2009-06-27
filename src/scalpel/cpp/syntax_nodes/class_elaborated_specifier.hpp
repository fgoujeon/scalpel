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

#ifndef SCALPEL_CPP_SYNTAX_NODES_CLASS_ELABORATED_SPECIFIER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_CLASS_ELABORATED_SPECIFIER_HPP

#include "common.hpp"
#include "class_key.hpp"
#include "nested_name_specifier.hpp"
#include "identifier.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
class_elaborated_specifier
	= class_key, ["::"], [nested_name_specifier], identifier
;
*/
typedef
	sequence_node
	<
		class_key,
		optional_node<space>,
		optional_node<predefined_text_node<str::double_colon>>,
		optional_node<space>,
		optional_node<nested_name_specifier>,
		optional_node<space>,
		identifier_or_template_id
	>
	class_elaborated_specifier_t
;

struct class_elaborated_specifier: public class_elaborated_specifier_t
{
	typedef class_elaborated_specifier_t type;
	typedef type::head_node_t head_node_t;
	typedef type::tail_sequence_node_t tail_sequence_node_t;

	class_elaborated_specifier
	(
		class_key&& o1,
		optional_node<space>&& o2,
		optional_node<predefined_text_node<str::double_colon>> o3,
		optional_node<space>&& o4,
		optional_node<nested_name_specifier>&& o5,
		optional_node<space>&& o6,
		identifier_or_template_id&& o7
	):
		type(o1, o2, o3, o4, o5, o6, o7)
	{
	}

	class_elaborated_specifier
	(
		head_node_t&& head,
		tail_sequence_node_t&& tail
	):
		type(head, tail)
	{
	}

	class_elaborated_specifier(type&& o): type(o)
	{
	}

	class_elaborated_specifier(const class_elaborated_specifier& o): type(o)
	{
	}

	class_elaborated_specifier(class_elaborated_specifier&& o): type(o)
	{
	}
};

inline
const identifier_or_template_id&
get_identifier_or_template_id(const class_elaborated_specifier& o)
{
	return get<6>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
