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

#include "namespace_.hpp"
#include "macros/detail/member_definition.hpp"
#include "macros/detail/single_member_definition.hpp"

#define GENERATE_NAMESPACE_DEFINITION( \
	CLASS_NAME, \
	NAMESPACE_TYPE, \
	UNNAMED_NAMESPACE_TYPE, \
	IS_NAMED, \
	CAN_HAVE_MULTIPLE_UNNAMED_NAMESPACES, \
	HAS_USING_DIRECTIVE_NAMESPACE_DECLARATION, \
	HAS_NAMESPACE_ALIASES, \
	HAS_ENTITY_ALIASES \
) \
CLASS_NAME::CLASS_NAME() \
{ \
} \
 \
BOOST_PP_IIF  \
(  \
	IS_NAMED,  \
	CLASS_NAME::CLASS_NAME(const std::string& name): \
		name_(name) \
	{ \
	}, \
)  \
 \
MEMBER_DEFINITION(CLASS_NAME, NAMESPACE_TYPE, namespaces, 1) \
BOOST_PP_IIF \
( \
	CAN_HAVE_MULTIPLE_UNNAMED_NAMESPACES, \
	MEMBER_DEFINITION(CLASS_NAME, UNNAMED_NAMESPACE_TYPE, unnamed_namespaces, 1), \
	SINGLE_MEMBER_DEFINITION(CLASS_NAME, UNNAMED_NAMESPACE_TYPE, unnamed_namespace) \
) \
BOOST_PP_IIF \
( \
	HAS_NAMESPACE_ALIASES, \
	MEMBER_DEFINITION(CLASS_NAME, namespace_alias, namespace_aliases, 0), \
) \
MEMBER_DEFINITION(CLASS_NAME, class_, classes, 1) \
MEMBER_DEFINITION(CLASS_NAME, enum_, enums, 1) \
MEMBER_DEFINITION(CLASS_NAME, typedef_, typedefs, 1) \
MEMBER_DEFINITION(CLASS_NAME, simple_function, simple_functions, 1) \
MEMBER_DEFINITION(CLASS_NAME, operator_function, operator_functions, 1) \
MEMBER_DEFINITION(CLASS_NAME, variable, variables, 1)

namespace scalpel { namespace cpp { namespace semantic_entities
{

GENERATE_NAMESPACE_DEFINITION(namespace_, namespace_, unnamed_namespace, 1, 0, 1, 1, 1)
GENERATE_NAMESPACE_DEFINITION(unnamed_namespace, namespace_, unnamed_namespace, 0, 0, 1, 1, 1)
GENERATE_NAMESPACE_DEFINITION(linked_namespace, linked_namespace, linked_unnamed_namespace, 1, 1, 0, 0, 0)
GENERATE_NAMESPACE_DEFINITION(linked_unnamed_namespace, linked_namespace, linked_unnamed_namespace, 0, 0, 0, 0, 0)

}}} //namespace scalpel::cpp::semantic_entities

#undef GENERATE_NAMESPACE_DEFINITION

#include "macros/detail/member_definition_undef.hpp"
#include "macros/detail/single_member_definition_undef.hpp"

