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

#define GENERATE_NAMESPACE_DEFINITION(CLASS_NAME, IS_NAMED) \
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
const CLASS_NAME::open_declarative_region_ptr_variants_t& \
CLASS_NAME::open_declarative_regions() \
{ \
	return open_declarative_regions_; \
} \
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
CLASS_NAME::unnamed_namespaces_t::range \
CLASS_NAME::unnamed_namespaces() \
{ \
	return unnamed_namespaces_; \
} \
 \
const CLASS_NAME::unnamed_namespaces_t& \
CLASS_NAME::unnamed_namespaces() const \
{ \
	return unnamed_namespaces_; \
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
CLASS_NAME::namespace_aliases_t::range \
CLASS_NAME::namespace_aliases() \
{ \
	return namespace_aliases_; \
} \
 \
const CLASS_NAME::namespace_aliases_t& \
CLASS_NAME::namespace_aliases() const \
{ \
	return namespace_aliases_; \
} \
 \
const CLASS_NAME::namespace_ptrs_t& \
CLASS_NAME::using_directive_namespaces() const \
{ \
	return using_directive_namespaces_; \
} \
 \
void \
CLASS_NAME::add_member(std::unique_ptr<namespace_>&& member) \
{ \
	member->enclosing_declarative_region(this); \
	open_declarative_regions_.push_back(member.get()); \
 \
    namespaces_.push_back(std::move(member)); \
} \
 \
void \
CLASS_NAME::add_member(std::unique_ptr<unnamed_namespace>&& member) \
{ \
	member->enclosing_declarative_region(this); \
	open_declarative_regions_.push_back(member.get()); \
 \
    unnamed_namespaces_.push_back(std::move(member)); \
} \
 \
void \
CLASS_NAME::add_member(std::unique_ptr<class_>&& member) \
{ \
	member->enclosing_declarative_region(this); \
	open_declarative_regions_.push_back(member.get()); \
 \
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
void \
CLASS_NAME::add_member(std::unique_ptr<namespace_alias>&& member) \
{ \
	open_declarative_regions_.push_back(member.get()); \
    namespace_aliases_.push_back(std::move(member)); \
} \
 \
void \
CLASS_NAME::add_using_directive_namespace(namespace_& n) \
{ \
	using_directive_namespaces_.push_back(&n); \
}

namespace scalpel { namespace cpp { namespace semantic_entities
{

GENERATE_NAMESPACE_DEFINITION(namespace_, 1)
GENERATE_NAMESPACE_DEFINITION(unnamed_namespace, 0)

}}} //namespace scalpel::cpp::semantic_entities

#undef GENERATE_NAMESPACE_DEFINITION

