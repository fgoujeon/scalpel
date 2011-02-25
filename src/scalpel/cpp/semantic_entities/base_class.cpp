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

#include "base_class.hpp"
#include "class_.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

base_class::base_class
(
	class_& base,
	const member_access access,
	bool is_virtual
):
	base_(&base),
	access_(access),
	is_virtual_(is_virtual)
{
}

}}} //namespace scalpel::cpp::semantic_entities

