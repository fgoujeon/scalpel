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

#include "enum.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

namespace
{
	struct: utility::static_visitor<const std::string&>
	{
		template<class T>
		const std::string&
		operator()(const T& e)
		{
			return e.name();
		}
	} get_name_visitor;
}

const std::string&
get_name(const enum_t& e)
{
	return apply_visitor(get_name_visitor, e);
}

const std::string&
get_name(const member_enum_t& e)
{
	return apply_visitor(get_name_visitor, e);
}

}}} //namespace scalpel::cpp::semantic_entities

