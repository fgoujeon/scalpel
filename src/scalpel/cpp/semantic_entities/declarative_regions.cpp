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

#include "declarative_regions.hpp"
#include "namespace_.hpp"
#include "namespace_alias.hpp"
#include "class_.hpp"
#include "functions.hpp"
#include "statement_block.hpp"
#include <scalpel/utility/extern_strings.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities
{

namespace
{
	struct: public utility::static_visitor<declarative_region_t>
	{
		template<class T>
		declarative_region_t
		operator()(T* t) const
		{
			return t;
		}
	} to_declarative_region_ptr_variant;

	struct: public utility::static_visitor<declarative_region_t>
	{
		template<class Entity>
		declarative_region_t
		operator()(Entity* t) const
		{
			return apply_visitor(to_declarative_region_ptr_variant, t->enclosing_declarative_region());
		}
	} get_enclosing_declarative_region_visitor;
}

declarative_region_t
get_enclosing_declarative_region(const declarative_region_t& var)
{
	return utility::apply_visitor(get_enclosing_declarative_region_visitor, var);
}

}}} //namespace scalpel::cpp::semantic_entities

