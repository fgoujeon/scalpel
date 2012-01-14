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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_OVERLOADABLE_OPERATOR_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_OVERLOADABLE_OPERATOR_HPP

namespace scalpel { namespace cpp { namespace semantic_entities
{

enum class overloadable_operator
{
	//new/delete
	NEW,
	NEW_ARRAY,
	DELETE,
	DELETE_ARRAY,

	//assignment
	EQUAL,

	//equality
	DOUBLE_EQUAL,
	EXCLAMATION_EQUAL,

	//comparison
	LEFT_ANGLE_BRACKET,
	RIGHT_ANGLE_BRACKET,
	LEFT_ANGLE_BRACKET_EQUAL,
	RIGHT_ANGLE_BRACKET_EQUAL,

	//arithmetic
	PLUS,
	MINUS,
	ASTERISK,
	SLASH,
	PERCENT,

	//arithmetic assignment
	PLUS_EQUAL,
	MINUS_EQUAL,
	ASTERISK_EQUAL,
	SLASH_EQUAL,
	PERCENT_EQUAL,
	DOUBLE_PLUS,
	DOUBLE_MINUS,

	//boolean
	DOUBLE_AMPERSAND,
	DOUBLE_PIPE,
	EXCLAMATION,

	//bitwise
	AMPERSAND,
	PIPE,
	CIRCUMFLEX,
	TILDE,
	DOUBLE_LEFT_ANGLE_BRACKET,
	DOUBLE_RIGHT_ANGLE_BRACKET,

	//bitmask and other bitwise assignment
	AMPERSAND_EQUAL,
	PIPE_EQUAL,
	CIRCUMFLEX_EQUAL,
	DOUBLE_LEFT_ANGLE_BRACKET_EQUAL,
	DOUBLE_RIGHT_ANGLE_BRACKET_EQUAL,

	//member access
	SQUARE_BRACKETS,
	ARROW,
	ARROW_ASTERISK,

	//other
	ROUND_BRACKETS,
	COMMA
};

}}} //namespace scalpel::cpp::semantic_entities

#endif

