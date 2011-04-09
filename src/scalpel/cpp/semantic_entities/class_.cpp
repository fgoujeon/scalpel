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
#include "macros/detail/member_definition.hpp"
#include "macros/detail/single_member_definition.hpp"
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
MEMBER_DEFINITION(CLASS_NAME, member_class, classes, 1) \
MEMBER_DEFINITION(CLASS_NAME, member_enum, enums, 1) \
MEMBER_DEFINITION(CLASS_NAME, member_typedef, typedefs, 1) \
MEMBER_DEFINITION(CLASS_NAME, constructor, constructors, 1) \
SINGLE_MEMBER_DEFINITION(CLASS_NAME, destructor, destructor) \
MEMBER_DEFINITION(CLASS_NAME, operator_member_function, operator_functions, 1) \
MEMBER_DEFINITION(CLASS_NAME, conversion_function, conversion_functions, 1) \
MEMBER_DEFINITION(CLASS_NAME, simple_member_function, simple_functions, 1) \
MEMBER_DEFINITION(CLASS_NAME, member_variable, variables, 1) \
MEMBER_DEFINITION(CLASS_NAME, bit_field, bit_fields, 1) \
 \
const CLASS_NAME::base_classes_t& \
CLASS_NAME::base_classes() const \
{ \
	return base_classes_; \
} \
 \
void \
CLASS_NAME::add_base_class(const base_class& bc) \
{ \
	base_classes_.push_back(bc); \
} \
 \
void \
CLASS_NAME::reset_destructor() \
{ \
	set_destructor \
	( \
		std::unique_ptr<destructor>(new destructor(member_access::PUBLIC, false)) \
	); \
}

namespace scalpel { namespace cpp { namespace semantic_entities
{

GENERATE_CLASS_DEFINITION(class_, 0)
GENERATE_CLASS_DEFINITION(member_class, 1)

}}} //namespace scalpel::cpp::semantic_entities

#undef GENERATE_CLASS_DEFINITION

#include "macros/detail/member_definition_undef.hpp"
#include "macros/detail/single_member_definition_undef.hpp"

