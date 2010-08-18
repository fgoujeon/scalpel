/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#include "get_members.hpp"
#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

#define GENERATE_SIMPLE_GET_MEMBERS_SPECIALIZATION(PARENT_TYPE, MEMBER_TYPE, PARENT_MEMBER_FUNCTION) \
template<> \
typename get_members_type_traits<semantic_entities::MEMBER_TYPE>::return_type \
get_members<semantic_entities::MEMBER_TYPE, std::shared_ptr<semantic_entities::PARENT_TYPE>>(std::shared_ptr<semantic_entities::PARENT_TYPE> parent) \
{ \
	return parent->PARENT_MEMBER_FUNCTION(); \
}

#define GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(PARENT_TYPE, MEMBER_TYPE) \
template<> \
typename get_members_type_traits<semantic_entities::MEMBER_TYPE>::return_type \
get_members<semantic_entities::MEMBER_TYPE, std::shared_ptr<semantic_entities::PARENT_TYPE>>(std::shared_ptr<semantic_entities::PARENT_TYPE>) \
{ \
	return get_members_type_traits<semantic_entities::MEMBER_TYPE>::return_type(); \
}

#define GENERATE_DECLARATIVE_REGION_VARIANT_GET_MEMBERS_SPECIALIZATION(MEMBER_TYPE) \
template<> \
typename get_members_type_traits<semantic_entities::MEMBER_TYPE>::return_type \
get_members<semantic_entities::MEMBER_TYPE, semantic_entities::declarative_region_shared_ptr_variant>(semantic_entities::declarative_region_shared_ptr_variant parent) \
{ \
	if(auto opt_shared_ptr = utility::get<std::shared_ptr<semantic_entities::namespace_>>(&parent)) \
		return get_members<semantic_entities::MEMBER_TYPE>(*opt_shared_ptr); \
	else if(auto opt_shared_ptr = utility::get<std::shared_ptr<semantic_entities::class_>>(&parent)) \
		return get_members<semantic_entities::MEMBER_TYPE>(*opt_shared_ptr); \
	else if(auto opt_shared_ptr = utility::get<std::shared_ptr<semantic_entities::simple_function>>(&parent)) \
		return get_members<semantic_entities::MEMBER_TYPE>(*opt_shared_ptr); \
	throw "get_members() error"; \
}

GENERATE_SIMPLE_GET_MEMBERS_SPECIALIZATION(namespace_, declarative_region_shared_ptr_variant, declarative_region_variants)
GENERATE_SIMPLE_GET_MEMBERS_SPECIALIZATION(namespace_, namespace_, namespaces)
GENERATE_SIMPLE_GET_MEMBERS_SPECIALIZATION(namespace_, class_, classes)
GENERATE_SIMPLE_GET_MEMBERS_SPECIALIZATION(namespace_, simple_function, simple_functions)
GENERATE_SIMPLE_GET_MEMBERS_SPECIALIZATION(namespace_, variable, variables)

GENERATE_SIMPLE_GET_MEMBERS_SPECIALIZATION(class_, declarative_region_shared_ptr_variant, declarative_region_variants)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION (class_, namespace_)
GENERATE_SIMPLE_GET_MEMBERS_SPECIALIZATION(class_, class_, nested_classes)
GENERATE_SIMPLE_GET_MEMBERS_SPECIALIZATION(class_, simple_function, simple_functions)
GENERATE_SIMPLE_GET_MEMBERS_SPECIALIZATION(class_, variable, variables)

GENERATE_SIMPLE_GET_MEMBERS_SPECIALIZATION(simple_function, declarative_region_shared_ptr_variant, declarative_region_variants)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION (simple_function, namespace_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION (simple_function, class_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION (simple_function, simple_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION (simple_function, variable)

GENERATE_DECLARATIVE_REGION_VARIANT_GET_MEMBERS_SPECIALIZATION(declarative_region_shared_ptr_variant)
GENERATE_DECLARATIVE_REGION_VARIANT_GET_MEMBERS_SPECIALIZATION(namespace_)
GENERATE_DECLARATIVE_REGION_VARIANT_GET_MEMBERS_SPECIALIZATION(class_)
GENERATE_DECLARATIVE_REGION_VARIANT_GET_MEMBERS_SPECIALIZATION(simple_function)
GENERATE_DECLARATIVE_REGION_VARIANT_GET_MEMBERS_SPECIALIZATION(variable)

}}}} //namespace scalpel::cpp::detail::semantic_analysis

