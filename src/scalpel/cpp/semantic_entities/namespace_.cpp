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
CLASS_NAME::namespaces_t::range \
CLASS_NAME::namespaces() \
{ \
	return namespaces_; \
} \
 \
const CLASS_NAME::namespaces_t& \
CLASS_NAME::namespaces() const \
{ \
	return namespaces_; \
} \
 \
CLASS_NAME::classes_t::range \
CLASS_NAME::classes() \
{ \
	return classes_; \
} \
 \
const CLASS_NAME::classes_t& \
CLASS_NAME::classes() const \
{ \
	return classes_; \
} \
 \
CLASS_NAME::enums_t::range \
CLASS_NAME::enums() \
{ \
	return enums_; \
} \
 \
const CLASS_NAME::enums_t& \
CLASS_NAME::enums() const \
{ \
	return enums_; \
} \
 \
CLASS_NAME::typedefs_t::range \
CLASS_NAME::typedefs() \
{ \
	return typedefs_; \
} \
 \
const CLASS_NAME::typedefs_t& \
CLASS_NAME::typedefs() const \
{ \
	return typedefs_; \
} \
 \
CLASS_NAME::simple_functions_t::range \
CLASS_NAME::simple_functions() \
{ \
	return simple_functions_; \
} \
 \
const CLASS_NAME::simple_functions_t& \
CLASS_NAME::simple_functions() const \
{ \
	return simple_functions_; \
} \
 \
CLASS_NAME::operator_functions_t::range \
CLASS_NAME::operator_functions() \
{ \
	return operator_functions_; \
} \
 \
const CLASS_NAME::operator_functions_t& \
CLASS_NAME::operator_functions() const \
{ \
	return operator_functions_; \
} \
 \
CLASS_NAME::variables_t::range \
CLASS_NAME::variables() \
{ \
	return variables_; \
} \
 \
const CLASS_NAME::variables_t& \
CLASS_NAME::variables() const \
{ \
	return variables_; \
} \
 \
void \
CLASS_NAME::add_member(std::unique_ptr<NAMESPACE_TYPE>&& member) \
{ \
	member->enclosing_declarative_region(this); \
    namespaces_.push_back(std::move(member)); \
} \
 \
BOOST_PP_IIF \
( \
	CAN_HAVE_MULTIPLE_UNNAMED_NAMESPACES, \
 \
	void \
	CLASS_NAME::add_member(std::unique_ptr<UNNAMED_NAMESPACE_TYPE>&& member) \
	{ \
		member->enclosing_declarative_region(this); \
		unnamed_namespaces_.push_back(std::move(member)); \
	}, \
 \
	void \
	CLASS_NAME::set_unnamed_namespace(std::unique_ptr<UNNAMED_NAMESPACE_TYPE>&& member) \
	{ \
		member->enclosing_declarative_region(this); \
		unnamed_namespace_ = std::move(member); \
	} \
) \
 \
void \
CLASS_NAME::add_member(std::unique_ptr<class_>&& member) \
{ \
	member->enclosing_declarative_region(this); \
    classes_.push_back(std::move(member)); \
} \
 \
void \
CLASS_NAME::add_member(std::unique_ptr<enum_>&& member) \
{ \
	member->enclosing_declarative_region(this); \
    enums_.push_back(std::move(member)); \
} \
 \
void \
CLASS_NAME::add_member(std::unique_ptr<typedef_>&& member) \
{ \
	member->enclosing_declarative_region(this); \
    typedefs_.push_back(std::move(member)); \
} \
 \
void \
CLASS_NAME::add_member(std::unique_ptr<simple_function>&& member) \
{ \
	member->enclosing_declarative_region(this); \
    simple_functions_.push_back(std::move(member)); \
} \
 \
void \
CLASS_NAME::add_member(std::unique_ptr<operator_function>&& member) \
{ \
	member->enclosing_declarative_region(this); \
    operator_functions_.push_back(std::move(member)); \
} \
 \
void \
CLASS_NAME::add_member(std::unique_ptr<variable>&& member) \
{ \
	member->enclosing_declarative_region(this); \
    variables_.push_back(std::move(member)); \
} \
 \
BOOST_PP_IIF \
( \
	HAS_NAMESPACE_ALIASES, \
	void \
	CLASS_NAME::add_member(std::unique_ptr<namespace_alias>&& member) \
	{ \
		namespace_aliases_.push_back(std::move(member)); \
	}, \
) \
 \
BOOST_PP_IIF \
( \
	HAS_USING_DIRECTIVE_NAMESPACES, \
	void \
	CLASS_NAME::add_using_directive_namespace(namespace_& n) \
	{ \
		using_directive_namespaces_.push_back(&n); \
	}, \
) \
 \
void \
CLASS_NAME::add_using_declaration_member(class_& member) \
{ \
	using_declaration_classes_.push_back(&member); \
} \
 \
void \
CLASS_NAME::add_using_declaration_member(variable& member) \
{ \
	using_declaration_variables_.push_back(&member); \
}

namespace scalpel { namespace cpp { namespace semantic_entities
{

GENERATE_NAMESPACE_DEFINITION(namespace_, namespace_, unnamed_namespace, 1, 0, 1, 1)
GENERATE_NAMESPACE_DEFINITION(unnamed_namespace, namespace_, unnamed_namespace, 0, 0, 1, 1)
GENERATE_NAMESPACE_DEFINITION(linked_namespace, linked_namespace, linked_unnamed_namespace, 1, 1, 0, 0)
GENERATE_NAMESPACE_DEFINITION(linked_unnamed_namespace, linked_namespace, linked_unnamed_namespace, 0, 0, 0, 0)

}}} //namespace scalpel::cpp::semantic_entities

#undef GENERATE_NAMESPACE_DEFINITION

