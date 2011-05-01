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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_NAMESPACE_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_NAMESPACE_HPP

#include "declarative_region_variants.hpp"
#include "namespace_alias.hpp"
#include "entity_alias.hpp"
#include "class_.hpp"
#include "enum_.hpp"
#include "functions.hpp"
#include "typedef_.hpp"
#include "variable.hpp"
#include "macros/detail/name_property.hpp"
#include "macros/detail/member_declaration.hpp"
#include "macros/detail/single_member_declaration.hpp"
#include "macros/detail/using_directive_namespace_declaration.hpp"
#include "macros/detail/declarative_region_member_impl.hpp"
#include "macros/detail/hpp/entity_aliases_of_type.hpp"
#include <scalpel/utility/unique_ptr_vector.hpp>
#include <scalpel/utility/vector_range.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <string>
#include <vector>
#include <memory>

#define GENERATE_NAMESPACE_DECLARATION( \
	CLASS_NAME, \
	NAMESPACE_TYPE, \
	UNNAMED_NAMESPACE_TYPE, \
	DECLARATIVE_REGION_MEMBER_IMPL_T, \
	IS_NAMED, \
	CAN_HAVE_MULTIPLE_UNNAMED_NAMESPACES, \
	HAS_USING_DIRECTIVE_NAMESPACE_DECLARATION, \
	HAS_NAMESPACE_ALIASES, \
	HAS_ENTITY_ALIASES \
) \
struct CLASS_NAME \
{ \
	CLASS_NAME(); \
 \
	BOOST_PP_IIF \
	( \
		IS_NAMED, \
		explicit CLASS_NAME(const std::string& name);, \
	) \
 \
	CLASS_NAME(const CLASS_NAME&) = delete; \
 \
	const CLASS_NAME& \
	operator=(const CLASS_NAME&) = delete; \
 \
	BOOST_PP_IIF(IS_NAMED, NAME_PROPERTY,) \
 \
	MEMBER_DECLARATION(NAMESPACE_TYPE, namespaces) \
	BOOST_PP_IIF \
	( \
		CAN_HAVE_MULTIPLE_UNNAMED_NAMESPACES, \
		MEMBER_DECLARATION(UNNAMED_NAMESPACE_TYPE, unnamed_namespaces), \
		SINGLE_MEMBER_DECLARATION(UNNAMED_NAMESPACE_TYPE, unnamed_namespace, 1) \
	) \
	BOOST_PP_IIF \
	( \
		HAS_NAMESPACE_ALIASES, \
		MEMBER_DECLARATION(namespace_alias, namespace_aliases), \
	) \
	MEMBER_DECLARATION(class_, classes) \
	MEMBER_DECLARATION(union_, unions) \
	MEMBER_DECLARATION(anonymous_union, anonymous_unions) \
	MEMBER_DECLARATION(enum_, enums) \
	MEMBER_DECLARATION(typedef_, typedefs) \
	MEMBER_DECLARATION(simple_function, simple_functions) \
	MEMBER_DECLARATION(operator_function, operator_functions) \
	MEMBER_DECLARATION(variable, variables) \
 \
	BOOST_PP_IIF \
	( \
		HAS_USING_DIRECTIVE_NAMESPACE_DECLARATION, \
		USING_DIRECTIVE_NAMESPACE_DECLARATION, \
	) \
	BOOST_PP_IIF \
	( \
		HAS_ENTITY_ALIASES, \
		ENTITY_ALIASES_OF_TYPE(class_, class) \
		ENTITY_ALIASES_OF_TYPE(union_, union) \
		ENTITY_ALIASES_OF_TYPE(enum_, enum) \
		ENTITY_ALIASES_OF_TYPE(typedef_, typedef) \
		ENTITY_ALIASES_OF_TYPE(simple_function, simple_function) \
		ENTITY_ALIASES_OF_TYPE(operator_function, operator_function) \
		ENTITY_ALIASES_OF_TYPE(variable, variable), \
	) \
 \
	DECLARATIVE_REGION_MEMBER_IMPL(DECLARATIVE_REGION_MEMBER_IMPL_T) \
};

namespace scalpel { namespace cpp { namespace semantic_entities
{

class namespace_;
class unnamed_namespace;
class linked_namespace;
class linked_unnamed_namespace;

typedef
	impl::detail::declarative_region_member_impl<namespace_, unnamed_namespace>
	namespace_declarative_region_member_impl_t
;

typedef
	impl::detail::declarative_region_member_impl<linked_namespace, linked_unnamed_namespace>
	linked_namespace_declarative_region_member_impl_t
;

GENERATE_NAMESPACE_DECLARATION(namespace_, namespace_, unnamed_namespace, namespace_declarative_region_member_impl_t, 1, 0, 1, 1, 1)
GENERATE_NAMESPACE_DECLARATION(unnamed_namespace, namespace_, unnamed_namespace, namespace_declarative_region_member_impl_t, 0, 0, 1, 1, 1)
GENERATE_NAMESPACE_DECLARATION(linked_unnamed_namespace, linked_namespace, linked_unnamed_namespace, linked_namespace_declarative_region_member_impl_t, 0, 0, 0, 0, 0)
GENERATE_NAMESPACE_DECLARATION(linked_namespace, linked_namespace, linked_unnamed_namespace, linked_namespace_declarative_region_member_impl_t, 1, 1, 0, 0, 0)

}}} //namespace scalpel::cpp::semantic_entities

#include "macros/detail/name_property_undef.hpp"
#include "macros/detail/member_declaration_undef.hpp"
#include "macros/detail/single_member_declaration_undef.hpp"
#include "macros/detail/using_directive_namespace_declaration_undef.hpp"
#include "macros/detail/declarative_region_member_impl_undef.hpp"
#include "macros/detail/hpp/entity_aliases_of_type_undef.hpp"

#endif

