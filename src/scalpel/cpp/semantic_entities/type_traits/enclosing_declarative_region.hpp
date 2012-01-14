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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_TYPE_TRAITS_ENCLOSING_DECLARATIVE_REGION_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_TYPE_TRAITS_ENCLOSING_DECLARATIVE_REGION_HPP

#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace type_traits
{

template<class Entity>
struct const_enclosing_declarative_region
{
	typedef typename Entity::const_enclosing_declarative_region_t type;
};

template<>
struct const_enclosing_declarative_region<enum_>
{
	typedef enum_declarative_region_member_impl_t::const_declarative_region_t type;
};

template<>
struct const_enclosing_declarative_region<member_enum>
{
	typedef member_enum_declarative_region_member_impl_t::const_declarative_region_t type;
};

}}}} //namespace scalpel::cpp::semantic_entities::type_traits

#endif

