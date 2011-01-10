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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_FUNCTION_TYPES_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_FUNCTION_TYPES_HPP

#include "type_variant_fwd.hpp"
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <vector>
#include <memory>

#define GENERATE_FUNCTION_TYPE_DECLARATION( \
	CLASS_NAME, \
	HAS_PARENT_CLASS, \
	HAS_CV_QUALIFIER \
) \
struct CLASS_NAME \
{ \
	public: \
		CLASS_NAME \
		( \
			BOOST_PP_IIF(HAS_PARENT_CLASS, const class_* parent_class,) BOOST_PP_COMMA_IF(HAS_PARENT_CLASS) \
			BOOST_PP_IIF(HAS_CV_QUALIFIER, const bool const_qualified,) BOOST_PP_COMMA_IF(HAS_CV_QUALIFIER) \
			BOOST_PP_IIF(HAS_CV_QUALIFIER, const bool volatile_qualified,) BOOST_PP_COMMA_IF(HAS_CV_QUALIFIER) \
			const type_variant& return_type, \
			const std::vector<type_variant>& parameter_types, \
			const bool variadic \
		); \
 \
		BOOST_PP_IIF \
		( \
			HAS_PARENT_CLASS, \
			const class_* parent_class;, \
		) \
		BOOST_PP_IIF \
		( \
			HAS_CV_QUALIFIER, \
			const bool const_qualified; \
			const bool volatile_qualified; \
			, \
		) \
		const type_variant return_type; \
		const std::vector<type_variant> parameter_types; \
		const bool variadic; \
}; \
 \
bool \
operator==(const CLASS_NAME& lhs, const CLASS_NAME& rhs);

namespace scalpel { namespace cpp { namespace semantic_entities
{

class class_;

GENERATE_FUNCTION_TYPE_DECLARATION(member_function_type, 1, 1)
GENERATE_FUNCTION_TYPE_DECLARATION(function_type,        0, 0)

}}} //namespace scalpel::cpp::semantic_entities

#undef GENERATE_FUNCTION_TYPE_DECLARATION

#endif

