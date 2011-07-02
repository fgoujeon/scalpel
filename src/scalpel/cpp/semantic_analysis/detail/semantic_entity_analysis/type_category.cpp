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

#include "type_category.hpp"
#include <scalpel/cpp/semantic_entities/fundamental_type.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail { namespace semantic_entity_analysis
{

using namespace semantic_entities;

namespace
{
	struct: utility::static_visitor<type_category>
	{
		template<typename T>
		type_category
		operator()(const T&)
		{
			return type_category::OTHER;
		}

		type_category
		operator()(const cv_qualified_type& type)
		{
			return get_category(type.qualified_type());
		}

		type_category
		operator()(const fundamental_type type)
		{
			switch(type)
			{
				case fundamental_type::BOOL:
					return type_category::BOOL;
				case fundamental_type::CHAR:
					return type_category::CHAR;
				case fundamental_type::WCHAR_T:
					return type_category::WCHAR_T;
				case fundamental_type::FLOAT:
					return type_category::FLOAT;
				case fundamental_type::DOUBLE:
					return type_category::DOUBLE;
				case fundamental_type::LONG_DOUBLE:
					return type_category::LONG_DOUBLE;
				case fundamental_type::INT:
					return type_category::INT;
				case fundamental_type::LONG_INT:
					return type_category::LONG_INT;
				case fundamental_type::LONG_LONG_INT:
					return type_category::LONG_LONG_INT;
				case fundamental_type::SHORT_INT:
					return type_category::SHORT_INT;
				case fundamental_type::SIGNED_CHAR:
					return type_category::SIGNED_CHAR;
				case fundamental_type::UNSIGNED_CHAR:
					return type_category::UNSIGNED_CHAR;
				case fundamental_type::UNSIGNED_INT:
					return type_category::UNSIGNED_INT;
				case fundamental_type::UNSIGNED_LONG_INT:
					return type_category::UNSIGNED_LONG_INT;
				case fundamental_type::UNSIGNED_LONG_LONG_INT:
					return type_category::UNSIGNED_LONG_LONG_INT;
				case fundamental_type::UNSIGNED_SHORT_INT:
					return type_category::UNSIGNED_SHORT_INT;
				default:
					return type_category::OTHER;
			}
		}
	} get_category_visitor;
}

type_category
get_category(const type_t& type)
{
	return apply_visitor(get_category_visitor, type);
}

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis

