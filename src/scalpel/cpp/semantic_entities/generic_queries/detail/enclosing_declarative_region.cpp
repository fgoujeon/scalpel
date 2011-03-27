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

#include "enclosing_declarative_region.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities { namespace generic_queries { namespace detail
{

namespace
{
	struct: utility::static_visitor<namespace_ptr_variant>
	{
		template<class Entity>
		namespace_ptr_variant
		operator()(Entity* entity) const
		{
			return entity;
		}
	} to_namespace_ptr_variant_visitor;

	struct: utility::static_visitor<namespace_ptr_variant>
	{
		template<class Entity>
		namespace_ptr_variant
		operator()(Entity* entity) const
		{
			const typename Entity::enclosing_declarative_region_t& enclosing_declarative_region =
				entity->enclosing_declarative_region()
			;
			return apply_visitor(to_namespace_ptr_variant_visitor, enclosing_declarative_region);
		}
	} enclosing_declarative_region_visitor;
}

namespace_ptr_variant
enclosing_declarative_region(const namespace_ptr_variant& entity)
{
	return apply_visitor(enclosing_declarative_region_visitor, entity);
}

}}}}} //namespace scalpel::cpp::semantic_entities::generic_queries::detail

