/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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

#include "typedef_.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

typedef_::typedef_(const std::string& name, const type_t& type):
	name_(name),
	type_(type)
{
}

member_typedef::member_typedef(const std::string& name, const type_t& type, const member_accessibility access):
	name_(name),
	type_(type),
	accessibility_(access)
{
}

}}} //namespace scalpel::cpp::semantic_entities

