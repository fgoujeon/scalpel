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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_CONVERSIONS_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_CONVERSIONS_HPP

#include "conversion.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

enum class conversion_tag
{
	INT,
	LONG_INT,
	UNSIGNED_INT,
	UNSIGNED_LONG_INT,
	FLOAT,
	DOUBLE,
	LONG_DOUBLE
};

typedef
	conversion<static_cast<int>(conversion_tag::INT)>
	conversion_to_int
;

typedef
	conversion<static_cast<int>(conversion_tag::LONG_INT)>
	conversion_to_long_int
;

typedef
	conversion<static_cast<int>(conversion_tag::UNSIGNED_INT)>
	conversion_to_unsigned_int
;

typedef
	conversion<static_cast<int>(conversion_tag::UNSIGNED_LONG_INT)>
	conversion_to_unsigned_long_int
;

typedef
	conversion<static_cast<int>(conversion_tag::FLOAT)>
	conversion_to_float
;

typedef
	conversion<static_cast<int>(conversion_tag::DOUBLE)>
	conversion_to_double
;

typedef
	conversion<static_cast<int>(conversion_tag::LONG_DOUBLE)>
	conversion_to_long_double
;

}}} //namespace scalpel::cpp::semantic_entities

#endif

