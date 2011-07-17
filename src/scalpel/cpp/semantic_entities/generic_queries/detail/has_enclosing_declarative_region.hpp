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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_GENERIC_QUERIES_DETAIL_HAS_ENCLOSING_DECLARATIVE_REGION_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_GENERIC_QUERIES_DETAIL_HAS_ENCLOSING_DECLARATIVE_REGION_HPP

#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace generic_queries { namespace detail
{

template<class Entity>
struct has_enclosing_declarative_region_impl
{
	static
	bool
	has(const Entity& entity)
	{
		return entity.has_enclosing_declarative_region();
	}
};



struct: utility::static_visitor<bool>
{
	template<class Entity>
	bool
	operator()(Entity* const entity) const
	{
		return entity->has_enclosing_declarative_region();
	}

	template<class Entity>
	bool
	operator()(const Entity& entity) const
	{
		return entity.has_enclosing_declarative_region();
	}
} has_enclosing_declarative_region_visitor;

template<class... Entities>
struct has_enclosing_declarative_region_impl<utility::variant<Entities...>>
{
	static
	bool
	has(const utility::variant<Entities...>& entity)
	{
		return apply_visitor(has_enclosing_declarative_region_visitor, entity);
	}
};



template<>
struct has_enclosing_declarative_region_impl<enum_t>
{
	static
	bool
	has(const enum_typedef& entity)
	{
		return apply_visitor(has_enclosing_declarative_region_visitor, entity);
	}
};



template<>
struct has_enclosing_declarative_region_impl<member_enum_t>
{
	static
	bool
	has(const member_enum_t& entity)
	{
		return apply_visitor(has_enclosing_declarative_region_visitor, entity);
	}
};



//public function
template<class Entity>
inline
bool
has_enclosing_declarative_region(const Entity& entity)
{
	return has_enclosing_declarative_region_impl<Entity>::has(entity);
}

}}}}} //namespace scalpel::cpp::semantic_entities::generic_queries::detail

#endif

