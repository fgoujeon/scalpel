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
#include <scalpel/utility/variant.hpp>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

//visitors for declarative region variants
template<class MemberT>
struct get_declarative_region_members_impl: public utility::static_visitor<typename get_members_type_traits<MemberT>::return_type>
{
	template<class T>
	typename get_members_type_traits<MemberT>::return_type
	operator()(std::shared_ptr<T> t) const
	{
		return get_members<MemberT>(t);
	}
};

#define GENERATE_SIMPLE_GET_MEMBERS_SPECIALIZATION(PARENT_TYPE, MEMBER_TYPE, PARENT_MEMBER_FUNCTION) \
template<> \
get_members_type_traits<semantic_entities::MEMBER_TYPE>::return_type \
get_members<semantic_entities::MEMBER_TYPE, std::shared_ptr<semantic_entities::PARENT_TYPE>>(std::shared_ptr<semantic_entities::PARENT_TYPE> parent) \
{ \
	return parent->PARENT_MEMBER_FUNCTION(); \
}

#define GENERATE_NAMESPACE_ALIAS_GET_MEMBERS_SPECIALIZATION(PARENT_TYPE, MEMBER_TYPE, PARENT_MEMBER_FUNCTION) \
template<> \
get_members_type_traits<semantic_entities::MEMBER_TYPE>::return_type \
get_members<semantic_entities::MEMBER_TYPE, std::shared_ptr<semantic_entities::PARENT_TYPE>>(std::shared_ptr<semantic_entities::PARENT_TYPE> parent) \
{ \
	return parent->referred_namespace()->PARENT_MEMBER_FUNCTION(); \
}

#define GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION(PARENT_TYPE, MEMBER_TYPE) \
template<> \
get_members_type_traits<semantic_entities::MEMBER_TYPE>::return_type \
get_members<semantic_entities::MEMBER_TYPE, std::shared_ptr<semantic_entities::PARENT_TYPE>>(std::shared_ptr<semantic_entities::PARENT_TYPE>) \
{ \
	return get_members_type_traits<semantic_entities::MEMBER_TYPE>::return_type(); \
}

#define GENERATE_DECLARATIVE_REGION_VARIANT_GET_MEMBERS_SPECIALIZATION(PARENT_TYPE, MEMBER_TYPE) \
template<> \
get_members_type_traits<semantic_entities::MEMBER_TYPE>::return_type \
get_members<semantic_entities::MEMBER_TYPE, semantic_entities::PARENT_TYPE>(semantic_entities::PARENT_TYPE parent) \
{ \
	get_declarative_region_members_impl<semantic_entities::MEMBER_TYPE> impl; \
	return utility::apply_visitor(impl, parent); \
}

GENERATE_SIMPLE_GET_MEMBERS_SPECIALIZATION(namespace_, open_declarative_region_shared_ptr_variant, open_declarative_regions)
GENERATE_SIMPLE_GET_MEMBERS_SPECIALIZATION(namespace_, namespace_, namespaces)
GENERATE_SIMPLE_GET_MEMBERS_SPECIALIZATION(namespace_, class_, classes)
GENERATE_SIMPLE_GET_MEMBERS_SPECIALIZATION(namespace_, simple_function, simple_functions)
GENERATE_SIMPLE_GET_MEMBERS_SPECIALIZATION(namespace_, variable, variables)
GENERATE_SIMPLE_GET_MEMBERS_SPECIALIZATION(namespace_, namespace_alias, namespace_aliases)

GENERATE_NAMESPACE_ALIAS_GET_MEMBERS_SPECIALIZATION(namespace_alias, open_declarative_region_shared_ptr_variant, open_declarative_regions)
GENERATE_NAMESPACE_ALIAS_GET_MEMBERS_SPECIALIZATION(namespace_alias, namespace_, namespaces)
GENERATE_NAMESPACE_ALIAS_GET_MEMBERS_SPECIALIZATION(namespace_alias, class_, classes)
GENERATE_NAMESPACE_ALIAS_GET_MEMBERS_SPECIALIZATION(namespace_alias, simple_function, simple_functions)
GENERATE_NAMESPACE_ALIAS_GET_MEMBERS_SPECIALIZATION(namespace_alias, variable, variables)
GENERATE_NAMESPACE_ALIAS_GET_MEMBERS_SPECIALIZATION(namespace_alias, namespace_alias, namespace_aliases)

GENERATE_SIMPLE_GET_MEMBERS_SPECIALIZATION(class_, open_declarative_region_shared_ptr_variant, open_declarative_regions)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION (class_, namespace_)
GENERATE_SIMPLE_GET_MEMBERS_SPECIALIZATION(class_, class_, nested_classes)
GENERATE_SIMPLE_GET_MEMBERS_SPECIALIZATION(class_, simple_function, simple_functions)
GENERATE_SIMPLE_GET_MEMBERS_SPECIALIZATION(class_, variable, variables)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION (class_, namespace_alias)

GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION (simple_function, open_declarative_region_shared_ptr_variant)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION (simple_function, namespace_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION (simple_function, class_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION (simple_function, simple_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION (simple_function, variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION (simple_function, namespace_alias)

/*
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION (operator_function, namespace_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION (operator_function, class_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION (operator_function, simple_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION (operator_function, variable)
*/

GENERATE_SIMPLE_GET_MEMBERS_SPECIALIZATION(statement_block, open_declarative_region_shared_ptr_variant, open_declarative_regions)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION (statement_block, namespace_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION (statement_block, class_)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION (statement_block, simple_function)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION (statement_block, variable)
GENERATE_EMPTY_GET_MEMBERS_SPECIALIZATION (statement_block, namespace_alias)

GENERATE_DECLARATIVE_REGION_VARIANT_GET_MEMBERS_SPECIALIZATION(declarative_region_shared_ptr_variant, open_declarative_region_shared_ptr_variant)
GENERATE_DECLARATIVE_REGION_VARIANT_GET_MEMBERS_SPECIALIZATION(declarative_region_shared_ptr_variant, namespace_)
GENERATE_DECLARATIVE_REGION_VARIANT_GET_MEMBERS_SPECIALIZATION(declarative_region_shared_ptr_variant, class_)
GENERATE_DECLARATIVE_REGION_VARIANT_GET_MEMBERS_SPECIALIZATION(declarative_region_shared_ptr_variant, simple_function)
GENERATE_DECLARATIVE_REGION_VARIANT_GET_MEMBERS_SPECIALIZATION(declarative_region_shared_ptr_variant, variable)
GENERATE_DECLARATIVE_REGION_VARIANT_GET_MEMBERS_SPECIALIZATION(declarative_region_shared_ptr_variant, namespace_alias)

GENERATE_DECLARATIVE_REGION_VARIANT_GET_MEMBERS_SPECIALIZATION(open_declarative_region_shared_ptr_variant, open_declarative_region_shared_ptr_variant)
GENERATE_DECLARATIVE_REGION_VARIANT_GET_MEMBERS_SPECIALIZATION(open_declarative_region_shared_ptr_variant, namespace_)
GENERATE_DECLARATIVE_REGION_VARIANT_GET_MEMBERS_SPECIALIZATION(open_declarative_region_shared_ptr_variant, class_)
GENERATE_DECLARATIVE_REGION_VARIANT_GET_MEMBERS_SPECIALIZATION(open_declarative_region_shared_ptr_variant, simple_function)
GENERATE_DECLARATIVE_REGION_VARIANT_GET_MEMBERS_SPECIALIZATION(open_declarative_region_shared_ptr_variant, variable)
GENERATE_DECLARATIVE_REGION_VARIANT_GET_MEMBERS_SPECIALIZATION(open_declarative_region_shared_ptr_variant, namespace_alias)

}}}} //namespace scalpel::cpp::detail::semantic_analysis

