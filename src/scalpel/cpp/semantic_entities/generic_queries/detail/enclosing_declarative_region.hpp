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

#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace generic_queries { namespace detail
{

struct: utility::static_visitor<namespace_::enclosing_declarative_region_t&>
{
	template<class Entity>
	namespace_::enclosing_declarative_region_t&
	operator()(Entity* entity) const
	{
		return entity->enclosing_declarative_region();
	}
} enclosing_declarative_region_visitor;

inline
namespace_::enclosing_declarative_region_t&
enclosing_declarative_region(namespace_ptr_variant& entity)
{
	return apply_visitor(enclosing_declarative_region_visitor, entity);
}

}}}}} //namespace scalpel::cpp::semantic_entities::generic_queries::detail

#endif

