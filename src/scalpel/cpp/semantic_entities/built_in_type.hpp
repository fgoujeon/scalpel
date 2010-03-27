/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_BUILT_IN_TYPE_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_BUILT_IN_TYPE_HPP

#include "type.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents a C++ built in type.
*/
class built_in_type: public type
{
	private:
		enum type_enum
		{
			BOOL,
			CHAR,
			DOUBLE,
			FLOAT,
			INT,
			LONG_DOUBLE,
			LONG_INT,
			LONG_LONG_INT,
			SHORT_INT,
			UNSIGNED_CHAR,
			UNSIGNED_INT,
			UNSIGNED_LONG_INT,
			UNSIGNED_LONG_LONG_INT,
			UNSIGNED_SHORT_INT,
			VOID,
			WCHAR_T
		};

		built_in_type(type_enum t);

		//
		//disable copy and move
		//
		built_in_type(const built_in_type&) = delete;

		built_in_type(built_in_type&&) = delete;

		const built_in_type&
		operator=(const built_in_type&) = delete;

		const built_in_type&
		operator=(built_in_type&&) = delete;

	public:
		bool
		operator==(const built_in_type& o) const;

		static const built_in_type bool_;
		static const built_in_type char_;
		static const built_in_type double_;
		static const built_in_type float_;
		static const built_in_type int_;
		static const built_in_type long_double;
		static const built_in_type long_int;
		static const built_in_type long_long_int;
		static const built_in_type short_int;
		static const built_in_type unsigned_char;
		static const built_in_type unsigned_int;
		static const built_in_type unsigned_long_int;
		static const built_in_type unsigned_long_long_int;
		static const built_in_type unsigned_short_int;
		static const built_in_type void_;
		static const built_in_type wchar_t_;

	private:
		type_enum type_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif
