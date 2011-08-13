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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_IS_MEMBER_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_IS_MEMBER_HPP

#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace type_traits
{

template<class Entity>
struct is_member
{
	static const bool value = false;
};

#define IS_MEMBER(ENTITY_TYPE) \
template<> \
struct is_member<ENTITY_TYPE> \
{ \
	static const bool value = true; \
};

IS_MEMBER(member_class)
IS_MEMBER(member_union)
IS_MEMBER(anonymous_member_union)
IS_MEMBER(member_enum)
IS_MEMBER(member_typedef)
IS_MEMBER(constructor)
IS_MEMBER(destructor)
IS_MEMBER(operator_member_function)
IS_MEMBER(conversion_function)
IS_MEMBER(simple_member_function)
IS_MEMBER(member_variable)
IS_MEMBER(static_member_variable)
IS_MEMBER(bit_field)

#undef IS_MEMBER

template<class T>
struct is_member<member_entity_alias<T>>
{
	static const bool value = true;
};

}}}} //namespace scalpel::cpp::semantic_entities::type_traits

#endif

