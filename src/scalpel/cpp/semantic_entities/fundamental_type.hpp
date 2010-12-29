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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_FUNDAMENTAL_TYPE_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_FUNDAMENTAL_TYPE_HPP

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents a C++ fundamental type.
*/
enum class fundamental_type
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

}}} //namespace scalpel::cpp::semantic_entities

#endif

