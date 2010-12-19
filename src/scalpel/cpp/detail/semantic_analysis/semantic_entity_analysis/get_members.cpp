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

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis { namespace semantic_entity_analysis
{

#define GENERATE_GET_MEMBERS_SPECIALIZATION(PARENT_TYPE, MEMBER_TYPE, PARENT_MEMBER_FUNCTION) \
template<> \
get_members_type_traits<semantic_entities::MEMBER_TYPE>::return_type \
get_members<semantic_entities::MEMBER_TYPE, std::shared_ptr<semantic_entities::PARENT_TYPE>>(std::shared_ptr<semantic_entities::PARENT_TYPE> parent) \
{ \
	return parent->PARENT_MEMBER_FUNCTION(); \
}

#define GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(PARENT_TYPE, MEMBER_TYPE) \
template<> \
get_members_type_traits<semantic_entities::MEMBER_TYPE>::return_type \
get_members<semantic_entities::MEMBER_TYPE, std::shared_ptr<semantic_entities::PARENT_TYPE>>(std::shared_ptr<semantic_entities::PARENT_TYPE>) \
{ \
	return get_members_type_traits<semantic_entities::MEMBER_TYPE>::return_type(); \
}

GENERATE_GET_MEMBERS_SPECIALIZATION      (namespace_, open_declarative_region_shared_ptr_variant, open_declarative_regions)
GENERATE_GET_MEMBERS_SPECIALIZATION      (namespace_, namespace_, namespaces)
GENERATE_GET_MEMBERS_SPECIALIZATION      (namespace_, class_, classes)
GENERATE_GET_MEMBERS_SPECIALIZATION      (namespace_, typedef_, typedefs)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(namespace_, constructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(namespace_, destructor)
GENERATE_GET_MEMBERS_SPECIALIZATION      (namespace_, operator_function, operator_functions)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(namespace_, operator_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(namespace_, conversion_function)
GENERATE_GET_MEMBERS_SPECIALIZATION      (namespace_, simple_function, simple_functions)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(namespace_, simple_member_function)
GENERATE_GET_MEMBERS_SPECIALIZATION      (namespace_, variable, variables)
GENERATE_GET_MEMBERS_SPECIALIZATION      (namespace_, namespace_alias, namespace_aliases)

GENERATE_GET_MEMBERS_SPECIALIZATION      (class_, open_declarative_region_shared_ptr_variant, open_declarative_regions)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(class_, namespace_)
GENERATE_GET_MEMBERS_SPECIALIZATION      (class_, class_, nested_classes)
GENERATE_GET_MEMBERS_SPECIALIZATION      (class_, typedef_, typedefs)
GENERATE_GET_MEMBERS_SPECIALIZATION      (class_, constructor, constructors)
GENERATE_GET_MEMBERS_SPECIALIZATION      (class_, destructor, get_destructor)
GENERATE_GET_MEMBERS_SPECIALIZATION      (class_, operator_function, operator_functions)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(class_, operator_member_function)
GENERATE_GET_MEMBERS_SPECIALIZATION      (class_, conversion_function, conversion_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION      (class_, simple_function, simple_functions)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(class_, simple_member_function)
GENERATE_GET_MEMBERS_SPECIALIZATION      (class_, variable, variables)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(class_, namespace_alias)

GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(constructor, open_declarative_region_shared_ptr_variant)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(constructor, namespace_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(constructor, class_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(constructor, typedef_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(constructor, constructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(constructor, destructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(constructor, operator_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(constructor, operator_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(constructor, conversion_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(constructor, simple_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(constructor, simple_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(constructor, variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(constructor, namespace_alias)

GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(destructor, open_declarative_region_shared_ptr_variant)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(destructor, namespace_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(destructor, class_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(destructor, typedef_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(destructor, constructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(destructor, destructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(destructor, operator_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(destructor, operator_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(destructor, conversion_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(destructor, simple_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(destructor, simple_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(destructor, variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(destructor, namespace_alias)

GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_function, open_declarative_region_shared_ptr_variant)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_function, namespace_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_function, class_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_function, typedef_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_function, constructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_function, destructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_function, operator_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_function, operator_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_function, conversion_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_function, simple_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_function, simple_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_function, variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_function, namespace_alias)

GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_member_function, open_declarative_region_shared_ptr_variant)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_member_function, namespace_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_member_function, class_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_member_function, typedef_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_member_function, constructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_member_function, destructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_member_function, operator_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_member_function, operator_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_member_function, conversion_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_member_function, simple_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_member_function, simple_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_member_function, variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(operator_member_function, namespace_alias)

GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(conversion_function, open_declarative_region_shared_ptr_variant)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(conversion_function, namespace_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(conversion_function, class_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(conversion_function, typedef_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(conversion_function, constructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(conversion_function, destructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(conversion_function, operator_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(conversion_function, operator_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(conversion_function, conversion_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(conversion_function, simple_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(conversion_function, simple_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(conversion_function, variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(conversion_function, namespace_alias)

GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_function, open_declarative_region_shared_ptr_variant)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_function, namespace_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_function, class_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_function, typedef_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_function, constructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_function, destructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_function, operator_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_function, operator_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_function, conversion_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_function, simple_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_function, simple_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_function, variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_function, namespace_alias)

GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_member_function, open_declarative_region_shared_ptr_variant)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_member_function, namespace_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_member_function, class_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_member_function, typedef_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_member_function, constructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_member_function, destructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_member_function, operator_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_member_function, operator_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_member_function, conversion_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_member_function, simple_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_member_function, simple_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_member_function, variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(simple_member_function, namespace_alias)

GENERATE_GET_MEMBERS_SPECIALIZATION      (statement_block, open_declarative_region_shared_ptr_variant, open_declarative_regions)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(statement_block, namespace_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(statement_block, class_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(statement_block, typedef_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(statement_block, constructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(statement_block, destructor)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(statement_block, operator_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(statement_block, operator_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(statement_block, conversion_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(statement_block, simple_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(statement_block, simple_member_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(statement_block, variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(statement_block, namespace_alias)

}}}}} //namespace scalpel::cpp::detail::semantic_analysis::semantic_entity_analysis

