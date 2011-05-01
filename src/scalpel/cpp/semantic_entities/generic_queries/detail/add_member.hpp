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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_GENERIC_QUERIES_DETAIL_ADD_MEMBER_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_GENERIC_QUERIES_DETAIL_ADD_MEMBER_HPP

#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace generic_queries { namespace detail
{

template<class DeclarativeRegion, class Entity>
inline
void
add_member(DeclarativeRegion& declarative_region, std::unique_ptr<Entity>&& entity)
{
	declarative_region.add_member(std::move(entity));
}

template<>
inline
void
add_member(class_& declarative_region, std::unique_ptr<destructor>&& entity)
{
	declarative_region.set_destructor(std::move(entity));
}

template<>
inline
void
add_member(member_class& declarative_region, std::unique_ptr<destructor>&& entity)
{
	declarative_region.set_destructor(std::move(entity));
}

template<>
inline
void
add_member(union_& declarative_region, std::unique_ptr<destructor>&& entity)
{
	declarative_region.set_destructor(std::move(entity));
}

template<>
inline
void
add_member(member_union& declarative_region, std::unique_ptr<destructor>&& entity)
{
	declarative_region.set_destructor(std::move(entity));
}

template<>
inline
void
add_member(anonymous_union&, std::unique_ptr<destructor>&&)
{
	assert(false);
}

template<>
inline
void
add_member(anonymous_member_union&, std::unique_ptr<destructor>&&)
{
	assert(false);
}

template<>
inline
void
add_member(linked_unnamed_namespace& declarative_region, std::unique_ptr<linked_unnamed_namespace>&& entity)
{
	assert(declarative_region.get_unnamed_namespace() == 0);
	declarative_region.set_unnamed_namespace(std::move(entity));
}

}}}}} //namespace scalpel::cpp::semantic_entities::generic_queries::detail

#endif

