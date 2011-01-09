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

#include "function_types.hpp"
#include "type_variants.hpp"

#define GENERATE_FUNCTION_TYPE_DEFINITION( \
	CLASS_NAME, \
	HAS_PARENT_CLASS, \
	HAS_CV_QUALIFIER, \
	HAS_RETURN_TYPE, \
	HAS_PARAMETERS \
) \
CLASS_NAME::CLASS_NAME \
( \
	BOOST_PP_IIF(HAS_PARENT_CLASS, const class_* parent_class_p,) BOOST_PP_COMMA_IF(HAS_PARENT_CLASS) \
	BOOST_PP_IIF(HAS_CV_QUALIFIER, const bool const_qualified_p,) BOOST_PP_COMMA_IF(HAS_CV_QUALIFIER) \
	BOOST_PP_IIF(HAS_CV_QUALIFIER, const bool volatile_qualified_p,) BOOST_PP_COMMA_IF(HAS_CV_QUALIFIER) \
	BOOST_PP_IIF(HAS_RETURN_TYPE, const type_variant& return_type_p,) BOOST_PP_COMMA_IF(HAS_RETURN_TYPE) \
	BOOST_PP_IIF(HAS_PARAMETERS, const std::vector<type_variant>& parameter_types_p,) BOOST_PP_COMMA_IF(HAS_PARAMETERS) \
	BOOST_PP_IIF(HAS_PARAMETERS, const bool variadic_p,) BOOST_PP_COMMA_IF(HAS_PARAMETERS) \
	void* const \
): \
	BOOST_PP_IIF(HAS_PARENT_CLASS, parent_class(parent_class_p),) BOOST_PP_COMMA_IF(HAS_PARENT_CLASS) \
	BOOST_PP_IIF(HAS_CV_QUALIFIER, const_qualified(const_qualified_p),) BOOST_PP_COMMA_IF(HAS_CV_QUALIFIER) \
	BOOST_PP_IIF(HAS_CV_QUALIFIER, volatile_qualified(volatile_qualified_p),) BOOST_PP_COMMA_IF(HAS_CV_QUALIFIER) \
	BOOST_PP_IIF(HAS_RETURN_TYPE, return_type(return_type_p),) BOOST_PP_COMMA_IF(HAS_RETURN_TYPE) \
	BOOST_PP_IIF(HAS_PARAMETERS, parameter_types(parameter_types_p),) BOOST_PP_COMMA_IF(HAS_PARAMETERS) \
	BOOST_PP_IIF(HAS_PARAMETERS, variadic(variadic_p),) BOOST_PP_COMMA_IF(HAS_PARAMETERS) \
	nothing_() \
{ \
} \
 \
bool \
operator==(const CLASS_NAME& lhs, const CLASS_NAME& rhs) \
{ \
	return \
		BOOST_PP_IIF(HAS_PARENT_CLASS, lhs.parent_class == rhs.parent_class &&,) \
		BOOST_PP_IIF(HAS_CV_QUALIFIER, lhs.const_qualified == rhs.const_qualified &&,) \
		BOOST_PP_IIF(HAS_CV_QUALIFIER, lhs.volatile_qualified == rhs.volatile_qualified &&,) \
		BOOST_PP_IIF(HAS_RETURN_TYPE, lhs.return_type == rhs.return_type &&,) \
		BOOST_PP_IIF(HAS_PARAMETERS, lhs.parameter_types == rhs.parameter_types &&,) \
		BOOST_PP_IIF(HAS_PARAMETERS, lhs.variadic == rhs.variadic &&,) \
		true \
	; \
}

namespace scalpel { namespace cpp { namespace semantic_entities
{

GENERATE_FUNCTION_TYPE_DEFINITION(constructor_type,     1, 0, 0, 1)
GENERATE_FUNCTION_TYPE_DEFINITION(destructor_type,      1, 0, 0, 0)
GENERATE_FUNCTION_TYPE_DEFINITION(member_function_type, 1, 1, 1, 1)
GENERATE_FUNCTION_TYPE_DEFINITION(function_type,        0, 0, 1, 1)

}}} //namespace scalpel::cpp::semantic_entities

#undef GENERATE_FUNCTION_TYPE_DEFINITION

