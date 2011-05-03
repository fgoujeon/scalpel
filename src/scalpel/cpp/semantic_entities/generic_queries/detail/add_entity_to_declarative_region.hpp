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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_GENERIC_QUERIES_DETAIL_ADD_ENTITY_TO_DECLARATIVE_REGION_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_GENERIC_QUERIES_DETAIL_ADD_ENTITY_TO_DECLARATIVE_REGION_HPP

#include "../../type_traits/has_members_of_type.hpp"
#include <scalpel/cpp/semantic_graph.hpp>
#include <boost/utility/enable_if.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace generic_queries { namespace detail
{

template<class DeclarativeRegion, class Entity>
inline
void
add_entity_to_declarative_region_ok
(
	DeclarativeRegion& declarative_region,
	std::unique_ptr<Entity>&& entity
)
{
	declarative_region.add_member(std::move(entity));
}

template<>
inline
void
add_entity_to_declarative_region_ok(class_& declarative_region, std::unique_ptr<destructor>&& entity)
{
	declarative_region.set_destructor(std::move(entity));
}

template<>
inline
void
add_entity_to_declarative_region_ok(member_class& declarative_region, std::unique_ptr<destructor>&& entity)
{
	declarative_region.set_destructor(std::move(entity));
}

template<>
inline
void
add_entity_to_declarative_region_ok(union_& declarative_region, std::unique_ptr<destructor>&& entity)
{
	declarative_region.set_destructor(std::move(entity));
}

template<>
inline
void
add_entity_to_declarative_region_ok(member_union& declarative_region, std::unique_ptr<destructor>&& entity)
{
	declarative_region.set_destructor(std::move(entity));
}

template<>
inline
void
add_entity_to_declarative_region_ok(anonymous_union&, std::unique_ptr<destructor>&&)
{
	assert(false);
}

template<>
inline
void
add_entity_to_declarative_region_ok(anonymous_member_union&, std::unique_ptr<destructor>&&)
{
	assert(false);
}

template<>
inline
void
add_entity_to_declarative_region_ok(linked_unnamed_namespace& declarative_region, std::unique_ptr<linked_unnamed_namespace>&& entity)
{
	assert(declarative_region.get_unnamed_namespace() == 0);
	declarative_region.set_unnamed_namespace(std::move(entity));
}



template<class DeclarativeRegion, class Entity>
inline
void
add_entity_to_declarative_region
(
	DeclarativeRegion& declarative_region,
	std::unique_ptr<Entity>&& entity,
	typename boost::enable_if<type_traits::has_members_of_type<DeclarativeRegion, Entity>>::type* = 0
)
{
	add_entity_to_declarative_region_ok(declarative_region, std::move(entity));
}

template<class DeclarativeRegion, class Entity>
inline
void
add_entity_to_declarative_region
(
	DeclarativeRegion&,
	std::unique_ptr<Entity>&&,
	typename boost::disable_if<type_traits::has_members_of_type<DeclarativeRegion, Entity>>::type* = 0
)
{
	throw std::runtime_error("This type of declarative region cannot contain this type of entity.");
}

}}}}} //namespace scalpel::cpp::semantic_entities::generic_queries::detail

#endif

