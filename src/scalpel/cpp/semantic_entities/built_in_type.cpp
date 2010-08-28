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

#include "built_in_type.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

built_in_type::built_in_type(type_enum t):
	type_(t)
{
}

bool
built_in_type::operator==(const built_in_type& o) const
{
	return type_ == o.type_;
}

bool
built_in_type::operator!=(const built_in_type& rhs) const
{
	return !operator==(rhs);
}

const built_in_type built_in_type::bool_(built_in_type::BOOL);
const built_in_type built_in_type::char_(built_in_type::CHAR);
const built_in_type built_in_type::double_(built_in_type::DOUBLE);
const built_in_type built_in_type::float_(built_in_type::FLOAT);
const built_in_type built_in_type::int_(built_in_type::INT);
const built_in_type built_in_type::long_double(built_in_type::LONG_DOUBLE);
const built_in_type built_in_type::long_int(built_in_type::LONG_INT);
const built_in_type built_in_type::long_long_int(built_in_type::LONG_LONG_INT);
const built_in_type built_in_type::short_int(built_in_type::SHORT_INT);
const built_in_type built_in_type::unsigned_char(built_in_type::UNSIGNED_CHAR);
const built_in_type built_in_type::unsigned_int(built_in_type::UNSIGNED_INT);
const built_in_type built_in_type::unsigned_long_int(built_in_type::UNSIGNED_LONG_INT);
const built_in_type built_in_type::unsigned_long_long_int(built_in_type::UNSIGNED_LONG_LONG_INT);
const built_in_type built_in_type::unsigned_short_int(built_in_type::UNSIGNED_SHORT_INT);
const built_in_type built_in_type::void_(built_in_type::VOID);
const built_in_type built_in_type::wchar_t_(built_in_type::WCHAR_T);

}}} //namespace scalpel::cpp::semantic_entities

