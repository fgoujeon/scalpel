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

//
//Stage 3
//

template<class Entity, class DeclarativeRegion>
struct add_entity_to_declarative_region_impl_3
{
	static
	void
	add
	(
		std::unique_ptr<Entity>&& entity,
		DeclarativeRegion& declarative_region
	)
	{
		declarative_region.add_member(std::move(entity));
	}
};

template<class DeclarativeRegion>
struct add_entity_to_declarative_region_impl_3<destructor, DeclarativeRegion>
{
	static
	void
	add
	(
		std::unique_ptr<destructor>&& entity,
		DeclarativeRegion& declarative_region
	)
	{
		declarative_region.set_destructor(std::move(entity));
	}
};

template<>
struct add_entity_to_declarative_region_impl_3<linked_unnamed_namespace, linked_unnamed_namespace>
{
	static
	void
	add
	(
		std::unique_ptr<linked_unnamed_namespace>&& entity,
		linked_unnamed_namespace& declarative_region
	)
	{
		assert(declarative_region.get_unnamed_namespace() == 0);
		declarative_region.set_unnamed_namespace(std::move(entity));
	}
};



//
//Stage 2
//

template<class Entity, class DeclarativeRegion>
inline
void
add_entity_to_declarative_region_2
(
	std::unique_ptr<Entity>&& entity,
	DeclarativeRegion& declarative_region,
	typename boost::enable_if<type_traits::has_members_of_type<DeclarativeRegion, Entity>>::type* = 0
)
{
	add_entity_to_declarative_region_impl_3<Entity, DeclarativeRegion>::add(std::move(entity), declarative_region);
}

template<class Entity, class DeclarativeRegion>
inline
void
add_entity_to_declarative_region_2
(
	std::unique_ptr<Entity>&&,
	DeclarativeRegion&,
	typename boost::disable_if<type_traits::has_members_of_type<DeclarativeRegion, Entity>>::type* = 0
)
{
	throw std::runtime_error("This type of declarative region cannot contain this type of entity.");
}



//
//Stage 1
//

template<class Entity, class DeclarativeRegion>
inline
void
add_entity_to_declarative_region
(
	std::unique_ptr<Entity>&& entity,
	DeclarativeRegion& declarative_region
)
{
	add_entity_to_declarative_region_2(std::move(entity), declarative_region);
}


template<class DeclarativeRegion>
class add_entity_to_declarative_region_visitor: public utility::static_visitor<void>
{
	public:
		add_entity_to_declarative_region_visitor(DeclarativeRegion& declarative_region):
			declarative_region_(declarative_region)
		{
		}

		template<class Entity>
		void
		operator()(Entity* entity)
		{
			add_entity_to_declarative_region_2(std::unique_ptr<Entity>(entity), declarative_region_);
		}

	private:
		DeclarativeRegion& declarative_region_;
};

template<class... Entities, class DeclarativeRegion>
inline
void
add_entity_to_declarative_region
(
	const utility::variant<Entities...>& entity_ptr_variant,
	DeclarativeRegion& declarative_region
)
{
	add_entity_to_declarative_region_visitor<DeclarativeRegion> visitor(declarative_region);
	apply_visitor(visitor, entity_ptr_variant);
}

}}}}} //namespace scalpel::cpp::semantic_entities::generic_queries::detail

#endif

