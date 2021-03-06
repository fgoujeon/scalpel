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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_HAS_ENTITY_ALIASES_OF_TYPE_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_HAS_ENTITY_ALIASES_OF_TYPE_HPP

#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace type_traits
{

template<class DeclarativeRegion, class Member>
struct has_entity_aliases_of_type
{
	static const bool value = false;
};

#define HAS_ENTITY_ALIASES_OF_TYPE(DECLARATIVE_REGION_TYPE, MEMBER_TYPE) \
template<> \
struct has_entity_aliases_of_type<DECLARATIVE_REGION_TYPE, MEMBER_TYPE> \
{ \
	static const bool value = true; \
};

HAS_ENTITY_ALIASES_OF_TYPE(namespace_, class_)
HAS_ENTITY_ALIASES_OF_TYPE(namespace_, enum_)
HAS_ENTITY_ALIASES_OF_TYPE(namespace_, typedef_)
HAS_ENTITY_ALIASES_OF_TYPE(namespace_, operator_function)
HAS_ENTITY_ALIASES_OF_TYPE(namespace_, simple_function)
HAS_ENTITY_ALIASES_OF_TYPE(namespace_, variable)

HAS_ENTITY_ALIASES_OF_TYPE(unnamed_namespace, class_)
HAS_ENTITY_ALIASES_OF_TYPE(unnamed_namespace, enum_)
HAS_ENTITY_ALIASES_OF_TYPE(unnamed_namespace, typedef_)
HAS_ENTITY_ALIASES_OF_TYPE(unnamed_namespace, operator_function)
HAS_ENTITY_ALIASES_OF_TYPE(unnamed_namespace, simple_function)
HAS_ENTITY_ALIASES_OF_TYPE(unnamed_namespace, variable)

HAS_ENTITY_ALIASES_OF_TYPE(class_, member_class)
HAS_ENTITY_ALIASES_OF_TYPE(class_, member_enum)
HAS_ENTITY_ALIASES_OF_TYPE(class_, member_typedef)
HAS_ENTITY_ALIASES_OF_TYPE(class_, operator_member_function)
HAS_ENTITY_ALIASES_OF_TYPE(class_, conversion_function)
HAS_ENTITY_ALIASES_OF_TYPE(class_, simple_member_function)
HAS_ENTITY_ALIASES_OF_TYPE(class_, member_variable)
HAS_ENTITY_ALIASES_OF_TYPE(class_, static_member_variable)
HAS_ENTITY_ALIASES_OF_TYPE(class_, bit_field)

HAS_ENTITY_ALIASES_OF_TYPE(member_class, member_class)
HAS_ENTITY_ALIASES_OF_TYPE(member_class, member_enum)
HAS_ENTITY_ALIASES_OF_TYPE(member_class, member_typedef)
HAS_ENTITY_ALIASES_OF_TYPE(member_class, operator_member_function)
HAS_ENTITY_ALIASES_OF_TYPE(member_class, conversion_function)
HAS_ENTITY_ALIASES_OF_TYPE(member_class, simple_member_function)
HAS_ENTITY_ALIASES_OF_TYPE(member_class, member_variable)
HAS_ENTITY_ALIASES_OF_TYPE(member_class, static_member_variable)
HAS_ENTITY_ALIASES_OF_TYPE(member_class, bit_field)

#undef HAS_ENTITY_ALIASES_OF_TYPE

}}}} //namespace scalpel::cpp::semantic_entities::type_traits

#endif

