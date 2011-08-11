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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_GENERIC_QUERIES_DETAIL_ENCLOSING_DECLARATIVE_REGION_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_GENERIC_QUERIES_DETAIL_ENCLOSING_DECLARATIVE_REGION_HPP

#include <scalpel/cpp/semantic_entities/type_traits/enclosing_declarative_region.hpp>
#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace generic_queries { namespace detail
{

namespace_ptr_variant
enclosing_declarative_region(const namespace_ptr_variant& entity);



template<class Entity>
typename type_traits::const_enclosing_declarative_region<Entity>::type&
get_enclosing_declarative_region(const Entity& entity)
{
	return entity.enclosing_declarative_region();
}

}}}}} //namespace scalpel::cpp::semantic_entities::generic_queries::detail

#endif

