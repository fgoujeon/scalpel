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

#include "create_unique_id.hpp"

namespace scalpel { namespace cpp { namespace linking { namespace detail
{

using namespace semantic_entities;

namespace
{
	std::string
	to_string(const overloadable_operator& op)
	{
		switch(op)
		{
			case overloadable_operator::NEW:
				return "new";
			case overloadable_operator::NEW_ARRAY:
				return "new[]";
			case overloadable_operator::DELETE:
				return "delete";
			case overloadable_operator::DELETE_ARRAY:
				return "delete[]";
			case overloadable_operator::DOUBLE_RIGHT_ANGLE_BRACKET_EQUAL:
				return ">>=";
			case overloadable_operator::DOUBLE_LEFT_ANGLE_BRACKET_EQUAL:
				return "<<=";
			case overloadable_operator::ARROW_ASTERISK:
				return "->*";
			case overloadable_operator::PLUS_EQUAL:
				return "+=";
			case overloadable_operator::MINUS_EQUAL:
				return "-=";
			case overloadable_operator::ASTERISK_EQUAL:
				return "*=";
			case overloadable_operator::SLASH_EQUAL:
				return "/=";
			case overloadable_operator::PERCENT_EQUAL:
				return "%=";
			case overloadable_operator::CIRCUMFLEX_EQUAL:
				return "^=";
			case overloadable_operator::AMPERSAND_EQUAL:
				return "&=";
			case overloadable_operator::PIPE_EQUAL:
				return "|=";
			case overloadable_operator::DOUBLE_LEFT_ANGLE_BRACKET:
				return "<<";
			case overloadable_operator::DOUBLE_RIGHT_ANGLE_BRACKET:
				return ">>";
			case overloadable_operator::DOUBLE_EQUAL:
				return "==";
			case overloadable_operator::EXCLAMATION_EQUAL:
				return "!=";
			case overloadable_operator::LEFT_ANGLE_BRACKET_EQUAL:
				return "<=";
			case overloadable_operator::RIGHT_ANGLE_BRACKET_EQUAL:
				return ">=";
			case overloadable_operator::DOUBLE_AMPERSAND:
				return "&&";
			case overloadable_operator::DOUBLE_PIPE:
				return "||";
			case overloadable_operator::DOUBLE_PLUS:
				return "++";
			case overloadable_operator::DOUBLE_MINUS:
				return "--";
			case overloadable_operator::ARROW:
				return "->";
			case overloadable_operator::ROUND_BRACKETS:
				return "()";
			case overloadable_operator::SQUARE_BRACKETS:
				return "[]";
			case overloadable_operator::COMMA:
				return ",";
			case overloadable_operator::PLUS:
				return "+";
			case overloadable_operator::MINUS:
				return "-";
			case overloadable_operator::ASTERISK:
				return "*";
			case overloadable_operator::SLASH:
				return "/";
			case overloadable_operator::PERCENT:
				return "%";
			case overloadable_operator::CIRCUMFLEX:
				return "^";
			case overloadable_operator::AMPERSAND:
				return "&";
			case overloadable_operator::PIPE:
				return "|";
			case overloadable_operator::TILDE:
				return "~";
			case overloadable_operator::EXCLAMATION:
				return "!";
			case overloadable_operator::EQUAL:
				return "=";
			case overloadable_operator::LEFT_ANGLE_BRACKET:
				return "<";
			case overloadable_operator::RIGHT_ANGLE_BRACKET:
				return ">";
		}

		assert(false);
		return "";
	}
}

std::string
create_unique_id(const semantic_entities::class_& entity)
{
	return entity.name();
}

std::string
create_unique_id(const semantic_entities::enum_& entity)
{
	return entity.name();
}

std::string
create_unique_id(const semantic_entities::typedef_& entity)
{
	return entity.name();
}

std::string
create_unique_id(const semantic_entities::constructor& entity)
{
	const std::string& class_name = utility::get<class_*>(entity.enclosing_declarative_region())->name();
	return class_name + "::" + class_name;
}

std::string
create_unique_id(const semantic_entities::destructor& entity)
{
	const std::string& class_name = utility::get<class_*>(entity.enclosing_declarative_region())->name();
	return class_name + "::~" + class_name;
}

std::string
create_unique_id(const semantic_entities::operator_member_function& entity)
{
	const std::string& class_name = utility::get<class_*>(entity.enclosing_declarative_region())->name();
	return class_name + "::" + to_string(entity.overloaded_operator());
}

std::string
create_unique_id(const semantic_entities::conversion_function& entity)
{
	const std::string& class_name = utility::get<class_*>(entity.enclosing_declarative_region())->name();
	return class_name + "::operator" + class_name;
}

std::string
create_unique_id(const semantic_entities::simple_member_function& entity)
{
	const std::string& class_name = utility::get<class_*>(entity.enclosing_declarative_region())->name();
	return class_name + "::" + entity.name();
}

std::string
create_unique_id(const semantic_entities::operator_function& entity)
{
	return to_string(entity.overloaded_operator());
}

std::string
create_unique_id(const semantic_entities::simple_function& entity)
{
	return entity.name();
}

std::string
create_unique_id(const semantic_entities::variable& entity)
{
	return entity.name();
}

}}}} //namespace scalpel::cpp::linking::detail

