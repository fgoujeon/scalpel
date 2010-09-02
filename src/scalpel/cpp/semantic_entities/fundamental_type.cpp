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

#include "fundamental_type.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

fundamental_type::fundamental_type(type_enum t):
	type_(t)
{
}

bool
fundamental_type::operator==(const fundamental_type& o) const
{
	return type_ == o.type_;
}

bool
fundamental_type::operator!=(const fundamental_type& rhs) const
{
	return !operator==(rhs);
}

const fundamental_type fundamental_type::bool_(fundamental_type::BOOL);
const fundamental_type fundamental_type::char_(fundamental_type::CHAR);
const fundamental_type fundamental_type::double_(fundamental_type::DOUBLE);
const fundamental_type fundamental_type::float_(fundamental_type::FLOAT);
const fundamental_type fundamental_type::int_(fundamental_type::INT);
const fundamental_type fundamental_type::long_double(fundamental_type::LONG_DOUBLE);
const fundamental_type fundamental_type::long_int(fundamental_type::LONG_INT);
const fundamental_type fundamental_type::long_long_int(fundamental_type::LONG_LONG_INT);
const fundamental_type fundamental_type::short_int(fundamental_type::SHORT_INT);
const fundamental_type fundamental_type::unsigned_char(fundamental_type::UNSIGNED_CHAR);
const fundamental_type fundamental_type::unsigned_int(fundamental_type::UNSIGNED_INT);
const fundamental_type fundamental_type::unsigned_long_int(fundamental_type::UNSIGNED_LONG_INT);
const fundamental_type fundamental_type::unsigned_long_long_int(fundamental_type::UNSIGNED_LONG_LONG_INT);
const fundamental_type fundamental_type::unsigned_short_int(fundamental_type::UNSIGNED_SHORT_INT);
const fundamental_type fundamental_type::void_(fundamental_type::VOID);
const fundamental_type fundamental_type::wchar_t_(fundamental_type::WCHAR_T);

}}} //namespace scalpel::cpp::semantic_entities

