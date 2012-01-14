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

#include "get_type_size.hpp"
#include <scalpel/cpp/semantic_entities/class_.hpp>
#include <scalpel/cpp/semantic_entities/variable.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail { namespace semantic_entity_analysis
{

using namespace semantic_entities;

namespace
{
	template<class Class>
	size_t
	get_class_size(const Class& c)
	{
		size_t size = 0;

		for(const member_variable& var: c.variables())
		{
			size += get_type_size(var.type());
		}

		for(const bit_field& var: c.bit_fields())
		{
			size += get_type_size(var.type());
		}

		return std::max(size, static_cast<size_t>(1)); //the size of an empty class is 1 byte
	}



	template<class Union>
	size_t
	get_union_size(const Union& u)
	{
		size_t size = 1; //size of an empty union

		for(const member_variable& var: u.variables())
		{
			size = std::max(size, get_type_size(var.type()));
		}

		for(const bit_field& var: u.bit_fields())
		{
			size = std::max(size, get_type_size(var.type()));
		}

		return size;
	}



	struct: utility::static_visitor<size_t>
	{
		template<typename UnderlyingType>
		size_t
		operator()(const enum_constant_list<UnderlyingType>&)
		{
			return sizeof(UnderlyingType);
		}

	} get_enum_size_visitor;

	template<class Enum>
	size_t
	get_enum_size(const Enum& e)
	{
		return apply_visitor(get_enum_size_visitor, e.constants());
	}



	struct: utility::static_visitor<size_t>
	{
		size_t
		operator()(const array&)
		{
			return sizeof(void*);
		}

		size_t
		operator()(const fundamental_type& type)
		{
			switch(type)
			{
				case fundamental_type::BOOL:
					return sizeof(bool);
				case fundamental_type::CHAR:
					return sizeof(char);
				case fundamental_type::DOUBLE:
					return sizeof(double);
				case fundamental_type::FLOAT:
					return sizeof(float);
				case fundamental_type::INT:
					return sizeof(int);
				case fundamental_type::LONG_DOUBLE:
					return sizeof(long double);
				case fundamental_type::LONG_INT:
					return sizeof(long int);
				case fundamental_type::LONG_LONG_INT:
					return sizeof(long long int);
				case fundamental_type::SHORT_INT:
					return sizeof(short int);
				case fundamental_type::SIGNED_CHAR:
					return sizeof(signed char);
				case fundamental_type::UNSIGNED_CHAR:
					return sizeof(unsigned char);
				case fundamental_type::UNSIGNED_INT:
					return sizeof(unsigned int);
				case fundamental_type::UNSIGNED_LONG_INT:
					return sizeof(unsigned long int);
				case fundamental_type::UNSIGNED_LONG_LONG_INT:
					return sizeof(unsigned long long int);
				case fundamental_type::UNSIGNED_SHORT_INT:
					return sizeof(unsigned short int);
				case fundamental_type::VOID:
					throw std::runtime_error("invalid use of sizeof to a void type");
				case fundamental_type::WCHAR_T:
					return sizeof(wchar_t);
			}

			assert(false);
		}

		size_t
		operator()(const function_type&)
		{
			throw std::runtime_error("invalid use of sizeof to a function type");
		}

		size_t
		operator()(const class_* const c)
		{
			return get_class_size(*c);
		}

		size_t
		operator()(const member_class* const c)
		{
			return get_class_size(*c);
		}

		size_t
		operator()(const union_* const u)
		{
			return get_union_size(*u);
		}

		size_t
		operator()(const member_union* const u)
		{
			return get_union_size(*u);
		}

		size_t
		operator()(const anonymous_union* const u)
		{
			return get_union_size(*u);
		}

		size_t
		operator()(const anonymous_member_union* const u)
		{
			return get_union_size(*u);
		}

		size_t
		operator()(const cv_qualified_type& type)
		{
			return apply_visitor(*this, type.qualified_type());
		}

		size_t
		operator()(const enum_* const e)
		{
			return get_enum_size(*e);
		}

		size_t
		operator()(const member_enum* const e)
		{
			return get_enum_size(*e);
		}

		size_t
		operator()(const pointer&)
		{
			return sizeof(void*);
		}

		size_t
		operator()(const pointer_to_member&)
		{
			return sizeof(void*);
		}

		size_t
		operator()(const reference& type)
		{
			return apply_visitor(*this, type.qualified_type());
		}
	} get_type_size_visitor;
}

size_t
get_type_size(const semantic_entities::type_t& type)
{
	return apply_visitor(get_type_size_visitor, type);
}

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis

