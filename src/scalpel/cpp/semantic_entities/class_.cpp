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

#include "class_.hpp"
#include "typedef_.hpp"
#include "functions.hpp"
#include "variable.hpp"
#include "type_variant.hpp"
#include <memory>

#define GENERATE_CLASS_DEFINITION(CLASS_NAME, IS_MEMBER) \
CLASS_NAME::CLASS_NAME \
( \
	const std::string& name BOOST_PP_COMMA_IF(IS_MEMBER) \
	BOOST_PP_IIF(IS_MEMBER, const member_access access,) \
): \
    name_(name), \
	BOOST_PP_IIF(IS_MEMBER, access_(access),) BOOST_PP_COMMA_IF(IS_MEMBER) \
	complete_(false) \
{ \
	reset_destructor(); \
} \
 \
const CLASS_NAME::base_classes_t& \
CLASS_NAME::base_classes() const \
{ \
	return base_classes_; \
} \
 \
CLASS_NAME::classes_t::range \
CLASS_NAME::nested_classes() \
{ \
	return nested_classes_; \
} \
 \
const CLASS_NAME::classes_t& \
CLASS_NAME::nested_classes() const \
{ \
	return nested_classes_; \
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
CLASS_NAME::constructors_t::range \
CLASS_NAME::constructors() \
{ \
	return constructors_; \
} \
 \
const CLASS_NAME::constructors_t& \
CLASS_NAME::constructors() const \
{ \
	return constructors_; \
} \
 \
destructor& \
CLASS_NAME::get_destructor() \
{ \
	return *destructor_; \
} \
 \
const destructor& \
CLASS_NAME::get_destructor() const \
{ \
	return *destructor_; \
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
CLASS_NAME::conversion_functions_t::range \
CLASS_NAME::conversion_functions() \
{ \
	return conversion_functions_; \
} \
 \
const CLASS_NAME::conversion_functions_t& \
CLASS_NAME::conversion_functions() const \
{ \
	return conversion_functions_; \
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
CLASS_NAME::bit_fields_t::range \
CLASS_NAME::bit_fields() \
{ \
	return bit_fields_; \
} \
 \
const CLASS_NAME::bit_fields_t& \
CLASS_NAME::bit_fields() const \
{ \
	return bit_fields_; \
} \
 \
void \
CLASS_NAME::add_base_class(const base_class& bc) \
{ \
	base_classes_.push_back(bc); \
} \
 \
void \
CLASS_NAME::add_member(std::unique_ptr<member_class>&& member) \
{ \
	member->enclosing_declarative_region(this); \
	nested_classes_.push_back(std::move(member)); \
} \
 \
void \
CLASS_NAME::add_member(std::unique_ptr<member_enum>&& member) \
{ \
	member->enclosing_declarative_region(this); \
    enums_.push_back(std::move(member)); \
} \
 \
void \
CLASS_NAME::add_member(std::unique_ptr<member_typedef>&& member) \
{ \
	member->enclosing_declarative_region(this); \
    typedefs_.push_back(std::move(member)); \
} \
 \
void \
CLASS_NAME::add_member(std::unique_ptr<constructor>&& member) \
{ \
	member->enclosing_declarative_region(this); \
    constructors_.push_back(std::move(member)); \
} \
 \
void \
CLASS_NAME::set_destructor(std::unique_ptr<destructor>&& member) \
{ \
	member->enclosing_declarative_region(this); \
	destructor_ = std::move(member); \
} \
 \
void \
CLASS_NAME::add_member(std::unique_ptr<destructor>&& member) \
{ \
	member->enclosing_declarative_region(this); \
	destructor_ = std::move(member); \
} \
 \
void \
CLASS_NAME::reset_destructor() \
{ \
	set_destructor \
	( \
		std::unique_ptr<destructor>(new destructor(member_access::PUBLIC, false)) \
	); \
} \
 \
void \
CLASS_NAME::add_member(std::unique_ptr<simple_member_function>&& member) \
{ \
	member->enclosing_declarative_region(this); \
    simple_functions_.push_back(std::move(member)); \
} \
 \
void \
CLASS_NAME::add_member(std::unique_ptr<operator_member_function>&& member) \
{ \
	member->enclosing_declarative_region(this); \
    operator_functions_.push_back(std::move(member)); \
} \
 \
void \
CLASS_NAME::add_member(std::unique_ptr<conversion_function>&& member) \
{ \
	member->enclosing_declarative_region(this); \
    conversion_functions_.push_back(std::move(member)); \
} \
 \
void \
CLASS_NAME::add_member(std::unique_ptr<member_variable>&& member) \
{ \
	member->enclosing_declarative_region(this); \
    variables_.push_back(std::move(member)); \
} \
 \
void \
CLASS_NAME::add_member(std::unique_ptr<bit_field>&& member) \
{ \
	member->enclosing_declarative_region(this); \
    bit_fields_.push_back(std::move(member)); \
}

namespace scalpel { namespace cpp { namespace semantic_entities
{

GENERATE_CLASS_DEFINITION(class_, 0)
GENERATE_CLASS_DEFINITION(member_class, 1)

}}} //namespace scalpel::cpp::semantic_entities

#undef GENERATE_CLASS_DEFINITION

