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
	to_string(const type_variant& n);

	std::string
	to_string(const std::vector<type_variant>& parameter_types);

	std::string
	create_global_unique_id(const declarative_region_ptr_variant& region);

	std::string
	create_global_unique_id(const typename utility::ptr_variant<class_, member_class>::type& region);

	std::string
	create_global_unique_id(const namespace_& entity);

	template<class Class>
	std::string
	create_global_unique_id(const Class& entity);

	std::string
	create_global_unique_id(const enum_& entity);
}

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

	std::string
	to_string(const fundamental_type type)
	{
		switch(type)
		{
			case fundamental_type::BOOL:
				return "bool";
			case fundamental_type::CHAR:
				return "char";
			case fundamental_type::DOUBLE:
				return "double";
			case fundamental_type::FLOAT:
				return "float";
			case fundamental_type::INT:
				return "int";
			case fundamental_type::LONG_DOUBLE:
				return "long double";
			case fundamental_type::LONG_INT:
				return "long int";
			case fundamental_type::LONG_LONG_INT:
				return "long long int";
			case fundamental_type::SHORT_INT:
				return "short int";
			case fundamental_type::SIGNED_CHAR:
				return "signed char";
			case fundamental_type::UNSIGNED_CHAR:
				return "unsigned char";
			case fundamental_type::UNSIGNED_INT:
				return "unsigned int";
			case fundamental_type::UNSIGNED_LONG_INT:
				return "unsigned long int";
			case fundamental_type::UNSIGNED_LONG_LONG_INT:
				return "unsigned long long int";
			case fundamental_type::UNSIGNED_SHORT_INT:
				return "unsigned short int";
			case fundamental_type::VOID:
				return "void";
			case fundamental_type::WCHAR_T:
				return "wchar_t";
		}

		assert(false);
		return "";
	}

	std::string
	to_string(const array& entity)
	{
		return to_string(entity.qualified_type()) + "[]";
	}

	std::string
	to_string(const reference& entity)
	{
		return to_string(entity.qualified_type()) + "&";
	}

	std::string
	to_string(const pointer& entity)
	{
		return to_string(entity.qualified_type()) + "*";
	}

	std::string
	to_string(const pointer_to_member& entity)
	{
		return to_string(entity.qualified_type()) + " " + create_global_unique_id(entity.parent_class()) + "::*";
	}

	std::string
	to_string(const enum_* entity)
	{
		return create_global_unique_id(*entity);
	}

	std::string
	to_string(const class_* entity)
	{
		return create_global_unique_id(*entity);
	}

	std::string
	to_string(const function_type& entity)
	{
		return to_string(entity.return_type()) + to_string(entity.parameter_types());
	}

	std::string
	to_string(const cv_qualified_type& entity)
	{
		switch(entity.qualification())
		{
			case cv_qualified_type::qualification_type::CONST_AND_VOLATILE:
				return to_string(entity.qualified_type()) + " const volatile";
			case cv_qualified_type::qualification_type::CONST:
				return to_string(entity.qualified_type()) + " const";
			case cv_qualified_type::qualification_type::VOLATILE:
				return to_string(entity.qualified_type()) + " volatile";
		}

		assert(false);
		return "";
	}



	struct: utility::static_visitor<std::string>
	{
		template<typename T>
		std::string
		operator()(const T& t)
		{
			return to_string(t);
		}
	} to_string_visitor;

	std::string
	to_string(const semantic_entities::type_variant& n)
	{
		return utility::apply_visitor(to_string_visitor, n);
	}

	std::string
	to_string(const std::vector<type_variant>& parameter_types)
	{
		std::string str = "(";

		if(!parameter_types.empty())
		{
			auto i = parameter_types.begin();
			str += to_string(*i);
			++i;
			for(; i != parameter_types.end(); ++i)
			{
				str += ',' + to_string(*i);
			}
		}

		return str + ')';
	}



	struct: utility::static_visitor<std::string>
	{
		template<typename T>
		std::string
		operator()(const T*)
		{
			assert(false);
			return "";
		}

		std::string
		operator()(const namespace_* entity)
		{
			return create_global_unique_id(*entity);
		}

		std::string
		operator()(const class_* entity)
		{
			return create_global_unique_id(*entity);
		}

		std::string
		operator()(const member_class* entity)
		{
			return create_global_unique_id(*entity);
		}
	} create_global_unique_id_visitor;

	std::string
	create_global_unique_id(const declarative_region_ptr_variant& region)
	{
		return utility::apply_visitor(create_global_unique_id_visitor, region);
	}

	std::string
	create_global_unique_id(const typename utility::ptr_variant<class_, member_class>::type& region)
	{
		return utility::apply_visitor(create_global_unique_id_visitor, region);
	}

	std::string
	create_global_unique_id(const namespace_& entity)
	{
		if(entity.has_enclosing_declarative_region())
			return create_global_unique_id(*entity.enclosing_declarative_region()) + "::" + entity.name();
		else
			return entity.name();
	}

	template<class Class>
	std::string
	create_global_unique_id(const Class& entity)
	{
		if(entity.has_enclosing_declarative_region())
			return create_global_unique_id(entity.enclosing_declarative_region()) + "::" + entity.name();
		else
			return entity.name();
	}

	std::string
	create_global_unique_id(const enum_& entity)
	{
		if(entity.has_enclosing_declarative_region())
			return create_global_unique_id(entity.enclosing_declarative_region()) + "::" + entity.name();
		else
			return entity.name();
	}
}

std::string
create_unique_id(const semantic_entities::class_& entity)
{
	return entity.name();
}

std::string
create_unique_id(const semantic_entities::member_class& entity)
{
	return entity.name();
}

std::string
create_unique_id(const semantic_entities::enum_& entity)
{
	return entity.name();
}

std::string
create_unique_id(const semantic_entities::member_enum& entity)
{
	return entity.name();
}

std::string
create_unique_id(const semantic_entities::typedef_& entity)
{
	return entity.name();
}

std::string
create_unique_id(const semantic_entities::member_typedef& entity)
{
	return entity.name();
}

std::string
create_unique_id(const semantic_entities::constructor& entity)
{
	return to_string(entity.parameter_types());;
}

std::string
create_unique_id(const semantic_entities::destructor&)
{
	return "";
}

std::string
create_unique_id(const semantic_entities::operator_member_function& entity)
{
	return to_string(entity.overloaded_operator()) + to_string(entity.parameter_types());;
}

std::string
create_unique_id(const semantic_entities::conversion_function& entity)
{
	return to_string(entity.return_type());
}

std::string
create_unique_id(const semantic_entities::simple_member_function& entity)
{
	return entity.name() + to_string(entity.parameter_types());;
}

std::string
create_unique_id(const semantic_entities::operator_function& entity)
{
	return to_string(entity.overloaded_operator()) + to_string(entity.parameter_types());;
}

std::string
create_unique_id(const semantic_entities::simple_function& entity)
{
	return entity.name() + to_string(entity.parameter_types());
}

std::string
create_unique_id(const semantic_entities::variable& entity)
{
	return entity.name();
}

std::string
create_unique_id(const semantic_entities::member_variable& entity)
{
	return entity.name();
}

}}}} //namespace scalpel::cpp::linking::detail

