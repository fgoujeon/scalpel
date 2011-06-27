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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SEMANTIC_ENTITY_ANALYSIS_TYPE_CATEGORY_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SEMANTIC_ENTITY_ANALYSIS_TYPE_CATEGORY_HPP

#include <scalpel/cpp/semantic_entities/type_variant.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail { namespace semantic_entity_analysis
{

enum class type_category
{
	BOOL,
	CHAR,
	WCHAR_T,
	INT,
	LONG_INT,
	LONG_LONG_INT,
	SHORT_INT,
	SIGNED_CHAR,
	UNSIGNED_CHAR,
	UNSIGNED_INT,
	UNSIGNED_LONG_INT,
	UNSIGNED_LONG_LONG_INT,
	UNSIGNED_SHORT_INT,
	FLOAT,
	DOUBLE,
	LONG_DOUBLE,
	ENUMERATION,
	POINTER_TO_DEFINED_TYPE,
	OTHER
};



//
//specific types
//

inline
bool
is_bool(const type_category cat)
{
	return cat == type_category::BOOL;
}

inline
bool
is_char(const type_category cat)
{
	return cat == type_category::CHAR;
}

inline
bool
is_wchar_t(const type_category cat)
{
	return cat == type_category::WCHAR_T;
}

inline
bool
is_signed_char(const type_category cat)
{
	return cat == type_category::SIGNED_CHAR;
}

inline
bool
is_short_int(const type_category cat)
{
	return cat == type_category::SHORT_INT;
}

inline
bool
is_long_int(const type_category cat)
{
	return cat == type_category::LONG_INT;
}

inline
bool
is_unsigned_char(const type_category cat)
{
	return cat == type_category::UNSIGNED_CHAR;
}

inline
bool
is_unsigned_short_int(const type_category cat)
{
	return cat == type_category::UNSIGNED_SHORT_INT;
}

inline
bool
is_unsigned_int(const type_category cat)
{
	return cat == type_category::UNSIGNED_INT;
}

inline
bool
is_unsigned_long_int(const type_category cat)
{
	return cat == type_category::UNSIGNED_LONG_INT;
}

inline
bool
is_float(const type_category cat)
{
	return cat == type_category::FLOAT;
}

inline
bool
is_double(const type_category cat)
{
	return cat == type_category::DOUBLE;
}

inline
bool
is_long_double(const type_category cat)
{
	return cat == type_category::LONG_DOUBLE;
}



//
//type categories
//

inline
bool
is_integral(const type_category cat)
{
	switch(cat)
	{
		case type_category::BOOL:
		case type_category::CHAR:
		case type_category::WCHAR_T:
		case type_category::INT:
		case type_category::LONG_INT:
		case type_category::LONG_LONG_INT:
		case type_category::SHORT_INT:
		case type_category::SIGNED_CHAR:
		case type_category::UNSIGNED_CHAR:
		case type_category::UNSIGNED_INT:
		case type_category::UNSIGNED_LONG_INT:
		case type_category::UNSIGNED_LONG_LONG_INT:
		case type_category::UNSIGNED_SHORT_INT:
			return true;
		default:
			return false;
	}
}

inline
bool
is_floating(const type_category cat)
{
	switch(cat)
	{
		case type_category::FLOAT:
		case type_category::DOUBLE:
		case type_category::LONG_DOUBLE:
			return true;
		default:
			return false;
	}
}

inline
bool
is_arithmetic(const type_category cat)
{
	return is_integral(cat) || is_floating(cat);
}

inline
bool
is_enumeration(const type_category cat)
{
	return cat == type_category::ENUMERATION;
}

inline
bool
is_pointer_to_defined_type(const type_category cat)
{
	return cat == type_category::POINTER_TO_DEFINED_TYPE;
}

inline
bool
is_arithmetic_or_enumeration(const type_category cat)
{
	return is_arithmetic(cat) || is_enumeration(cat);
}

inline
bool
is_integral_or_enumeration(const type_category cat)
{
	return is_integral(cat) || is_enumeration(cat);
}



type_category
get_category(const semantic_entities::type_variant& type);

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis

#endif

