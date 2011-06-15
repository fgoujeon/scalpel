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

#ifndef SCALPEL_CPP_SYNTAX_NODES_CHARACTER_LITERAL_HPP
#define SCALPEL_CPP_SYNTAX_NODES_CHARACTER_LITERAL_HPP

#include "leaf_node.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class source_character_set: public leaf_node
{
	public:
		source_character_set
		(
			std::string&& value
		):
			leaf_node(value)
		{
		}

		source_character_set(const source_character_set& o):
			leaf_node(o)
		{
		}

		source_character_set(source_character_set&& o):
			leaf_node(o)
		{
		}
};

class universal_character_name: public leaf_node
{
	public:
		universal_character_name
		(
			std::string&& value
		):
			leaf_node(value)
		{
		}

		universal_character_name(const universal_character_name& o):
			leaf_node(o)
		{
		}

		universal_character_name(universal_character_name&& o):
			leaf_node(o)
		{
		}
};

class simple_escape_sequence: public leaf_node
{
	public:
		simple_escape_sequence
		(
			std::string&& value
		):
			leaf_node(value)
		{
		}

		simple_escape_sequence(const simple_escape_sequence& o):
			leaf_node(o)
		{
		}

		simple_escape_sequence(simple_escape_sequence&& o):
			leaf_node(o)
		{
		}
};

class octal_escape_sequence: public leaf_node
{
	public:
		octal_escape_sequence
		(
			std::string&& value
		):
			leaf_node(value)
		{
		}

		octal_escape_sequence(const octal_escape_sequence& o):
			leaf_node(o)
		{
		}

		octal_escape_sequence(octal_escape_sequence&& o):
			leaf_node(o)
		{
		}
};

class hexadecimal_escape_sequence: public leaf_node
{
	public:
		hexadecimal_escape_sequence
		(
			std::string&& value
		):
			leaf_node(value)
		{
		}

		hexadecimal_escape_sequence(const hexadecimal_escape_sequence& o):
			leaf_node(o)
		{
		}

		hexadecimal_escape_sequence(hexadecimal_escape_sequence&& o):
			leaf_node(o)
		{
		}
};

typedef
	alternative_node
	<
		simple_escape_sequence,
		octal_escape_sequence,
		hexadecimal_escape_sequence
	>
	escape_sequence
;

typedef
	alternative_node
	<
		source_character_set,
		escape_sequence,
		universal_character_name
	>
	c_char
;

typedef
	list_node<c_char>
	c_char_sequence
;

/*
character_literal
	= !ch_p('L') >> no_node_d[ch_p('\'')] >> c_char_sequence >> no_node_d[ch_p('\'')]
;
*/
typedef
	sequence_node
	<
		optional_node<predefined_text_node<str::capital_l>>,
		c_char_sequence
	>
	character_literal
;

inline
bool
has_leading_l(const character_literal& o)
{
	return get<0>(o);
}

inline
const c_char_sequence
get_char_sequence(const character_literal& o)
{
	return get<1>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif

