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

#define MEMBERS_OF_TYPE(CLASS_NAME, TYPE, NAME, SET_ENCLOSING_DECLARATIVE_REGION) \
CLASS_NAME::NAME##_t::range \
CLASS_NAME::NAME() \
{ \
	return NAME##_; \
} \
 \
const CLASS_NAME::NAME##_t& \
CLASS_NAME::NAME() const \
{ \
	return NAME##_; \
} \
 \
void \
CLASS_NAME::add_member(std::unique_ptr<TYPE>&& member) \
{ \
	BOOST_PP_IIF(SET_ENCLOSING_DECLARATIVE_REGION, member->enclosing_declarative_region(this);,) \
    NAME##_.push_back(std::move(member)); \
}



#define MEMBER_OF_TYPE(CLASS_NAME, TYPE, NAME) \
void \
CLASS_NAME::set_##NAME(std::unique_ptr<TYPE>&& member) \
{ \
	member->enclosing_declarative_region(this); \
	NAME##_ = std::move(member); \
}



#define GENERATE_NAMESPACE_DEFINITION( \
	CLASS_NAME, \
	NAMESPACE_TYPE, \
	UNNAMED_NAMESPACE_TYPE, \
	IS_NAMED, \
	CAN_HAVE_MULTIPLE_UNNAMED_NAMESPACES, \
	HAS_NAMESPACE_ALIASES, \
	HAS_USING_DIRECTIVE_NAMESPACES \
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
MEMBERS_OF_TYPE(CLASS_NAME, NAMESPACE_TYPE, namespaces, 1) \
BOOST_PP_IIF \
( \
	CAN_HAVE_MULTIPLE_UNNAMED_NAMESPACES, \
	MEMBERS_OF_TYPE(CLASS_NAME, UNNAMED_NAMESPACE_TYPE, unnamed_namespaces, 1), \
	MEMBER_OF_TYPE(CLASS_NAME, UNNAMED_NAMESPACE_TYPE, unnamed_namespace) \
) \
BOOST_PP_IIF \
( \
	HAS_NAMESPACE_ALIASES, \
	MEMBERS_OF_TYPE(CLASS_NAME, namespace_alias, namespace_aliases, 0), \
) \
MEMBERS_OF_TYPE(CLASS_NAME, class_, classes, 1) \
MEMBERS_OF_TYPE(CLASS_NAME, enum_, enums, 1) \
MEMBERS_OF_TYPE(CLASS_NAME, typedef_, typedefs, 1) \
MEMBERS_OF_TYPE(CLASS_NAME, simple_function, simple_functions, 1) \
MEMBERS_OF_TYPE(CLASS_NAME, operator_function, operator_functions, 1) \
MEMBERS_OF_TYPE(CLASS_NAME, variable, variables, 1)

namespace scalpel { namespace cpp { namespace semantic_entities
{

GENERATE_NAMESPACE_DEFINITION(namespace_, namespace_, unnamed_namespace, 1, 0, 1, 1)
GENERATE_NAMESPACE_DEFINITION(unnamed_namespace, namespace_, unnamed_namespace, 0, 0, 1, 1)
GENERATE_NAMESPACE_DEFINITION(linked_namespace, linked_namespace, linked_unnamed_namespace, 1, 1, 0, 0)
GENERATE_NAMESPACE_DEFINITION(linked_unnamed_namespace, linked_namespace, linked_unnamed_namespace, 0, 0, 0, 0)

}}} //namespace scalpel::cpp::semantic_entities

#undef GENERATE_NAMESPACE_DEFINITION
#undef MEMBERS_OF_TYPE
#undef MEMBER_OF_TYPE

