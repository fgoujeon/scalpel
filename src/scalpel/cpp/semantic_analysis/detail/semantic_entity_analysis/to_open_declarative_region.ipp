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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SEMANTIC_ENTITY_ANALYSIS_TO_OPEN_DECLARATIVE_REGION_IPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SEMANTIC_ENTITY_ANALYSIS_TO_OPEN_DECLARATIVE_REGION_IPP

#include <scalpel/cpp/semantic_entities/declarative_regions.hpp>
#include <scalpel/utility/ptr_variant.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail { namespace semantic_entity_analysis
{

template<class... Entities>
struct to_open_declarative_region_visitor: utility::static_visitor<semantic_entities::open_declarative_region_t>
{
	template<class Entity>
	semantic_entities::open_declarative_region_t
	operator()(Entity&) const
	{
		assert(false);
	}

	semantic_entities::open_declarative_region_t
	operator()(semantic_entities::namespace_* const entity) const
	{
		return entity;
	}

	semantic_entities::open_declarative_region_t
	operator()(semantic_entities::class_* const entity) const
	{
		return entity;
	}

	semantic_entities::open_declarative_region_t
	operator()(semantic_entities::member_class* const entity) const
	{
		return entity;
	}

	semantic_entities::open_declarative_region_t
	operator()(semantic_entities::union_* const entity) const
	{
		return entity;
	}

	semantic_entities::open_declarative_region_t
	operator()(semantic_entities::member_union* const entity) const
	{
		return entity;
	}

	semantic_entities::open_declarative_region_t
	operator()(semantic_entities::enum_* const entity) const
	{
		return entity;
	}

	semantic_entities::open_declarative_region_t
	operator()(semantic_entities::member_enum* const entity) const
	{
		return entity;
	}

	semantic_entities::open_declarative_region_t
	operator()(semantic_entities::namespace_alias* const alias) const
	{
		return &alias->referred_namespace();
	}

	semantic_entities::open_declarative_region_t
	operator()(semantic_entities::typedef_* const entity) const
	{
		return to_open_declarative_region(entity->type());
	}

	semantic_entities::open_declarative_region_t
	operator()(const semantic_entities::cv_qualified_type& entity) const
	{
		return to_open_declarative_region(entity.qualified_type());
	}
};

template<class... Entities>
semantic_entities::open_declarative_region_t
to_open_declarative_region(const utility::variant<Entities...>& var)
{
	to_open_declarative_region_visitor<Entities...> visitor;
	return apply_visitor(visitor, var);
}

template<class... Entities>
boost::optional<semantic_entities::open_declarative_region_t>
to_open_declarative_region(const boost::optional<utility::variant<Entities...>>& var)
{
	if(var)
		return to_open_declarative_region(*var);
	else
		return boost::optional<semantic_entities::open_declarative_region_t>();
}

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis

#endif

