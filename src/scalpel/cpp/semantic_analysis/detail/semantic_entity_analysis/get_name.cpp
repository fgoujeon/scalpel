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

#include "get_name.hpp"
#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail { namespace semantic_entity_analysis
{

#define GENERATE_SIMPLE_GET_NAME_SPECIALIZATION(ENTITY_TYPE) \
template<> \
const std::string& \
get_name<std::shared_ptr<semantic_entities::ENTITY_TYPE>>(const std::shared_ptr<semantic_entities::ENTITY_TYPE>& entity) \
{ \
	return entity->name(); \
} \
\
template<> \
const std::string& \
get_name<std::shared_ptr<semantic_entities::ENTITY_TYPE const>>(const std::shared_ptr<semantic_entities::ENTITY_TYPE const>& entity) \
{ \
	return entity->name(); \
}

template<>
const std::string&
get_name<semantic_entities::declarative_region_ptr_variant>(const semantic_entities::declarative_region_ptr_variant& entity)
{
	return semantic_entities::get_name(entity);
}

template<>
const std::string&
get_name<semantic_entities::open_declarative_region_ptr_variant>(const semantic_entities::open_declarative_region_ptr_variant& entity)
{
	return semantic_entities::get_name(entity);
}

GENERATE_SIMPLE_GET_NAME_SPECIALIZATION(namespace_alias)
GENERATE_SIMPLE_GET_NAME_SPECIALIZATION(namespace_)
GENERATE_SIMPLE_GET_NAME_SPECIALIZATION(class_)
GENERATE_SIMPLE_GET_NAME_SPECIALIZATION(enum_)
GENERATE_SIMPLE_GET_NAME_SPECIALIZATION(typedef_)
GENERATE_SIMPLE_GET_NAME_SPECIALIZATION(simple_member_function)
GENERATE_SIMPLE_GET_NAME_SPECIALIZATION(simple_function)
GENERATE_SIMPLE_GET_NAME_SPECIALIZATION(variable)

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis

