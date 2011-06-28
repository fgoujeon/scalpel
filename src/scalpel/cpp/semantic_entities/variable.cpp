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

#include "variable.hpp"

#define GENERATE_VARIABLE_DEFINITION( \
	CLASS_NAME, \
	IS_MEMBER, \
	HAS_STATIC, \
	HAS_SIZE \
) \
CLASS_NAME::CLASS_NAME \
( \
	const std::string& name, \
	const type_t& type BOOST_PP_COMMA_IF(HAS_SIZE) \
	BOOST_PP_IIF(HAS_SIZE, unsigned int size,) BOOST_PP_COMMA_IF(HAS_STATIC) \
	BOOST_PP_IIF(HAS_STATIC, bool is_static,) BOOST_PP_COMMA_IF(IS_MEMBER) \
	BOOST_PP_IIF(IS_MEMBER, const bool is_mutable,) BOOST_PP_COMMA_IF(IS_MEMBER) \
	BOOST_PP_IIF(IS_MEMBER, const member_access access,) \
): \
	name_(name), \
	type_(type) BOOST_PP_COMMA_IF(HAS_SIZE) \
	BOOST_PP_IIF(HAS_SIZE, size_(size),) BOOST_PP_COMMA_IF(HAS_STATIC) \
	BOOST_PP_IIF(HAS_STATIC, is_static_(is_static),) BOOST_PP_COMMA_IF(IS_MEMBER) \
	BOOST_PP_IIF(IS_MEMBER, is_mutable_(is_mutable),) BOOST_PP_COMMA_IF(IS_MEMBER) \
	BOOST_PP_IIF(IS_MEMBER, access_(access),) \
{ \
}

namespace scalpel { namespace cpp { namespace semantic_entities
{

GENERATE_VARIABLE_DEFINITION(variable, 0, 1, 0)
GENERATE_VARIABLE_DEFINITION(member_variable, 1, 1, 0)
GENERATE_VARIABLE_DEFINITION(bit_field, 1, 0, 1)

}}} //namespace scalpel::cpp::semantic_entities

#undef GENERATE_VARIABLE_DEFINITION

