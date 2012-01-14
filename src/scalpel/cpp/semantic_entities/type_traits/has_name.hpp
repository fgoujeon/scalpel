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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_HAS_NAME_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_HAS_NAME_HPP

#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace type_traits
{

template<class DeclarativeRegion>
struct has_name
{
	static const bool value = false;
};

#define HAS_NAME(ENTITY_TYPE) \
template<> \
struct has_name<ENTITY_TYPE> \
{ \
	static const bool value = true; \
};

HAS_NAME(namespace_alias)
HAS_NAME(namespace_)
HAS_NAME(linked_namespace)
HAS_NAME(class_)
HAS_NAME(member_class)
HAS_NAME(union_)
HAS_NAME(member_union)
HAS_NAME(enum_)
HAS_NAME(member_enum)
HAS_NAME(typedef_)
HAS_NAME(member_typedef)
HAS_NAME(simple_member_function)
HAS_NAME(simple_function)
HAS_NAME(variable)
HAS_NAME(member_variable)
HAS_NAME(bit_field)

#undef HAS_NAME

}}}} //namespace scalpel::cpp::semantic_entities::type_traits

#endif

