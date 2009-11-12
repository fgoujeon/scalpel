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
			CHAR,
			WCHAR_T,
			BOOL,
			SHORT,
			INT,
			LONG,
			SIGNED,
			UNSIGNED,
			FLOAT,
			DOUBLE,
			VOID
		};

		built_in_type(type_enum t);

	public:
		bool
		operator==(const built_in_type& o) const;

		static const built_in_type char_;
		static const built_in_type wchar_t_;
		static const built_in_type bool_;
		static const built_in_type short_;
		static const built_in_type int_;
		static const built_in_type long_;
		static const built_in_type signed_;
		static const built_in_type unsigned_;
		static const built_in_type float_;
		static const built_in_type double_;
		static const built_in_type void_;

	private:
		type_enum type_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif
