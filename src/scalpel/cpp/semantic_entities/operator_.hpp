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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_OPERATOR_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_OPERATOR_HPP

namespace scalpel { namespace cpp { namespace semantic_entities
{

enum operator_
{
	NEW,
	DELETE,
	//DOUBLE_RIGHT_ANGLE_BRACKET_EQUAL,
	//DOUBLE_LEFT_ANGLE_BRACKET_EQUAL,
	//ARROW_ASTERISK,
	//PLUS_EQUAL,
	//MINUS_EQUAL,
	//ASTERISK_EQUAL,
	//SLASH_EQUAL,
	//PERCENT_EQUAL,
	//CIRCUMFLEX_EQUAL,
	//AMPERSAND_EQUAL,
	//PIPE_EQUAL,
	//DOUBLE_LEFT_ANGLE_BRACKET,
	//DOUBLE_RIGHT_ANGLE_BRACKET,
	EQUALITY,
	INEQUALITY,
	//LEFT_ANGLE_BRACKET_EQUAL,
	//RIGHT_ANGLE_BRACKET_EQUAL,
	LOGICAL_AND,
	LOGICAL_OR,
	INCREMENT,
	DECREMENT,
	//ARROW,
	//ROUND_BRACKETS,
	//SQUARE_BRACKETS,
	//COMMA,
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDE,
	MODULO,
	BITWISE_EXCLUSIVE_OR,
	BITWISE_AND,
	BITWISE_OR,
	BITWISE_NOT,
	NOT,
	ASSIGNMENT,
	GREATER_THAN,
	LESS_THAN
};

}}} //namespace scalpel::cpp::semantic_entities

#endif
