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
#include <sstream>

namespace scalpel { namespace cpp { namespace linking { namespace detail
{

using namespace semantic_entities;

template<class... Entities>
std::string
create_unique_id(const utility::variant<Entities...>& entity);

namespace
{
	std::string
	to_string(const type_variant& n);

	std::string
	to_string(const std::vector<type_variant>& parameter_types);
}

namespace
{
	std::string
	to_string(const overloadable_operator& op)
	{
		std::ostringstream oss;
		oss << "@o" << static_cast<unsigned int>(op);
		return oss.str();
	}



	struct: utility::static_visitor<std::string>
	{
		std::string
		operator()(const fundamental_type type)
		{
			std::ostringstream oss;
			oss << "@t" << static_cast<unsigned int>(type);
			return oss.str();
		}

		std::string
		operator()(const array& entity)
		{
			return to_string(entity.qualified_type()) + "[]";
		}

		std::string
		operator()(const reference& entity)
		{
			return to_string(entity.qualified_type()) + "&";
		}

		std::string
		operator()(const pointer& entity)
		{
			return to_string(entity.qualified_type()) + "*";
		}

		std::string
		operator()(const pointer_to_member& entity)
		{
			return to_string(entity.qualified_type()) + " " + create_unique_id(entity.parent_class()) + "::*";
		}

		std::string
		operator()(const enum_* entity)
		{
			return create_unique_id(*entity);
		}

		std::string
		operator()(const member_enum* entity)
		{
			return create_unique_id(*entity);
		}

		std::string
		operator()(const class_* entity)
		{
			return create_unique_id(*entity);
		}

		std::string
		operator()(const member_class* entity)
		{
			return create_unique_id(*entity);
		}

		std::string
		operator()(const function_type& entity)
		{
			return to_string(entity.return_type()) + to_string(entity.parameter_types());
		}

		std::string
		operator()(const cv_qualified_type& entity)
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

	template<class Function>
	std::string
	function_cv_qualifiers_to_string(const Function& entity)
	{
		if(entity.is_const() && entity.is_volatile())
			return "const volatile";
		else if(entity.is_const())
			return "const";
		else if(entity.is_const() && entity.is_volatile())
			return "volatile";
		else
			return "";
	}

	template<class Entity>
	std::string
	create_enclosing_declarative_region_unique_id(const Entity& entity)
	{
		typedef typename Entity::const_enclosing_declarative_region_t enclosing_declarative_region_t;

		if(entity.has_enclosing_declarative_region())
		{
			const enclosing_declarative_region_t& enclosing_declarative_region =
				entity.enclosing_declarative_region()
			;

			//if(enclosing_declarative_region.has_enclosing_declarative_region()) //global namespace?
			{
				return create_unique_id(enclosing_declarative_region) + "::";
			}
		}

		return "";
	}
}



namespace
{
	struct: utility::static_visitor<std::string>
	{
		template<typename T>
		std::string
		operator()(const T& t)
		{
			return create_unique_id(t);
		}

		template<typename T>
		std::string
		operator()(const T* t)
		{
			return create_unique_id(*t);
		}

		template<typename T>
		std::string
		operator()(T* const& t)
		{
			return create_unique_id(*t);
		}
	} create_unique_id_visitor;
}

template<class... Entities>
std::string
create_unique_id(const utility::variant<Entities...>& entity)
{
	return apply_visitor(create_unique_id_visitor, entity);
}

std::string
create_unique_id(const semantic_entities::namespace_& entity)
{
	return create_enclosing_declarative_region_unique_id(entity) + entity.name();
}

std::string
create_unique_id(const semantic_entities::class_& entity)
{
	return create_enclosing_declarative_region_unique_id(entity) + entity.name();
}

std::string
create_unique_id(const semantic_entities::member_class& entity)
{
	return create_enclosing_declarative_region_unique_id(entity) + entity.name();
}

std::string
create_unique_id(const semantic_entities::enum_& entity)
{
	return create_enclosing_declarative_region_unique_id(entity) + entity.name();
}

std::string
create_unique_id(const semantic_entities::member_enum& entity)
{
	return create_enclosing_declarative_region_unique_id(entity) + entity.name();
}

std::string
create_unique_id(const semantic_entities::typedef_& entity)
{
	return create_enclosing_declarative_region_unique_id(entity) + entity.name();
}

std::string
create_unique_id(const semantic_entities::member_typedef& entity)
{
	return create_enclosing_declarative_region_unique_id(entity) + entity.name();
}

std::string
create_unique_id(const semantic_entities::constructor& entity)
{
	return create_enclosing_declarative_region_unique_id(entity) + to_string(entity.parameter_types());
}

std::string
create_unique_id(const semantic_entities::destructor& entity)
{
	return create_enclosing_declarative_region_unique_id(entity);
}

std::string
create_unique_id(const semantic_entities::operator_member_function& entity)
{
	return
		create_enclosing_declarative_region_unique_id(entity) +
		to_string(entity.overloaded_operator()) +
		to_string(entity.parameter_types()) +
		function_cv_qualifiers_to_string(entity)
	;
}

std::string
create_unique_id(const semantic_entities::conversion_function& entity)
{
	return
		create_enclosing_declarative_region_unique_id(entity) +
		to_string(entity.return_type()) +
		function_cv_qualifiers_to_string(entity)
	;
}

std::string
create_unique_id(const semantic_entities::simple_member_function& entity)
{
	return
		create_enclosing_declarative_region_unique_id(entity) +
		entity.name() +
		to_string(entity.parameter_types()) +
		function_cv_qualifiers_to_string(entity)
	;
}

std::string
create_unique_id(const semantic_entities::operator_function& entity)
{
	return
		create_enclosing_declarative_region_unique_id(entity) +
		to_string(entity.overloaded_operator()) +
		to_string(entity.parameter_types())
	;
}

std::string
create_unique_id(const semantic_entities::simple_function& entity)
{
	return
		create_enclosing_declarative_region_unique_id(entity) +
		entity.name() +
		to_string(entity.parameter_types())
	;
}

std::string
create_unique_id(const semantic_entities::variable& entity)
{
	return
		create_enclosing_declarative_region_unique_id(entity) +
		entity.name()
	;
}

std::string
create_unique_id(const semantic_entities::member_variable& entity)
{
	return
		create_enclosing_declarative_region_unique_id(entity) +
		entity.name()
	;
}

}}}} //namespace scalpel::cpp::linking::detail

