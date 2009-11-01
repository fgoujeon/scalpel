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
	public:
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

		inline
		type_enum
		get_type() const;

	private:
		type_enum type_;
};

inline
built_in_type::type_enum
built_in_type::get_type() const
{
	return type_;
}

}}} //namespace scalpel::cpp::semantic_entities

#endif
