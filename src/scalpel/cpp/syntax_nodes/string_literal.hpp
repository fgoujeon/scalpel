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

#ifndef SCALPEL_CPP_SYNTAX_NODES_STRING_LITERAL_HPP
#define SCALPEL_CPP_SYNTAX_NODES_STRING_LITERAL_HPP

#include "character_literal.hpp"
#include "leaf_node.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef
	alternative_node
	<
		source_character_set,
		escape_sequence,
		universal_character_name,
		universal_character_name //just so that s_char != c_char, not actually used
	>
	s_char
;

typedef
	list_node<s_char>
	s_char_sequence
;

typedef
	sequence_node
	<
		optional_node<predefined_text_node<str::capital_l>>,
		optional_node<s_char_sequence>
	>
	single_string_literal
;

inline
bool
has_leading_l(const single_string_literal& o)
{
	return get<0>(o);
}

inline
const optional_node<s_char_sequence>&
get_char_sequence(const single_string_literal& o)
{
	return get<1>(o);
}

typedef
	list_node<single_string_literal>
	string_literal
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif

