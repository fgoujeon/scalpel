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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_HAS_ENTITY_ALIASES_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_HAS_ENTITY_ALIASES_HPP

#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace type_traits
{

template<class DeclarativeRegion>
struct has_entity_aliases
{
	static const bool value = false;
};

#define HAS_ENTITY_ALIASES(DECLARATIVE_REGION_TYPE) \
template<> \
struct has_entity_aliases<DECLARATIVE_REGION_TYPE> \
{ \
	static const bool value = true; \
};

HAS_ENTITY_ALIASES(namespace_)
HAS_ENTITY_ALIASES(unnamed_namespace)
HAS_ENTITY_ALIASES(class_)
HAS_ENTITY_ALIASES(member_class)

#undef HAS_ENTITY_ALIASES

}}}} //namespace scalpel::cpp::semantic_entities::type_traits

#endif

