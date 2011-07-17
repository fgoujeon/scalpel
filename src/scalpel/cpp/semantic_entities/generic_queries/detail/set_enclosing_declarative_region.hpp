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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_GENERIC_QUERIES_DETAIL_SET_ENCLOSING_DECLARATIVE_REGION_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_GENERIC_QUERIES_DETAIL_SET_ENCLOSING_DECLARATIVE_REGION_HPP

#include <scalpel/cpp/semantic_entities/enum.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace generic_queries { namespace detail
{

template<class Entity, class DeclarativeRegion>
void
set_enclosing_declarative_region(Entity& entity, DeclarativeRegion& declarative_region)
{
	entity.enclosing_declarative_region(declarative_region);
}



template<class DeclarativeRegion>
class set_enclosing_declarative_region_visitor: public utility::static_visitor<void>
{
	public:
		set_enclosing_declarative_region_visitor(DeclarativeRegion& declarative_region):
			declarative_region_(declarative_region)
		{
		}

		/*
		template<class Entity>
		void
		operator()(Entity& entity)
		{
			entity.enclosing_declarative_region(declarative_region_);
		}
		*/

		template<typename T>
		void
		operator()(basic_enum<T>& entity)
		{
			entity.enclosing_declarative_region(declarative_region_);
		}

		template<typename T>
		void
		operator()(basic_member_enum<T>& entity)
		{
			entity.enclosing_declarative_region(declarative_region_);
		}

	private:
		DeclarativeRegion& declarative_region_;
};

template<class DeclarativeRegion>
void
set_enclosing_declarative_region(enum_t& entity, DeclarativeRegion& declarative_region)
{
	set_enclosing_declarative_region_visitor<DeclarativeRegion> visitor(declarative_region);
	apply_visitor(visitor, entity);
}

template<class DeclarativeRegion>
void
set_enclosing_declarative_region(member_enum_t& entity, DeclarativeRegion& declarative_region)
{
	set_enclosing_declarative_region_visitor<DeclarativeRegion> visitor(declarative_region);
	apply_visitor(visitor, entity);
}

}}}}} //namespace scalpel::cpp::semantic_entities::generic_queries::detail

#endif

