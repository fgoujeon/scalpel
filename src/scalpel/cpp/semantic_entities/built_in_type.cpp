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

const built_in_type built_in_type::char_ = built_in_type(built_in_type::CHAR);
const built_in_type built_in_type::wchar_t_ = built_in_type(built_in_type::WCHAR_T);
const built_in_type built_in_type::bool_ = built_in_type(built_in_type::BOOL);
const built_in_type built_in_type::short_ = built_in_type(built_in_type::SHORT);
const built_in_type built_in_type::int_ = built_in_type(built_in_type::INT);
const built_in_type built_in_type::long_ = built_in_type(built_in_type::LONG);
const built_in_type built_in_type::signed_ = built_in_type(built_in_type::SIGNED);
const built_in_type built_in_type::unsigned_ = built_in_type(built_in_type::UNSIGNED);
const built_in_type built_in_type::float_ = built_in_type(built_in_type::FLOAT);
const built_in_type built_in_type::double_ = built_in_type(built_in_type::DOUBLE);
const built_in_type built_in_type::void_ = built_in_type(built_in_type::VOID);

}}} //namespace scalpel::cpp::semantic_entities

