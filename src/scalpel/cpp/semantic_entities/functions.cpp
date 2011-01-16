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

#include "functions.hpp"
#include "type_variant.hpp"
#include <scalpel/utility/ptr_variant_conversion_functions.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/logical/or.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>

#define GENERATE_FUNCTION_DEFINITION( \
	CLASS_NAME, \
	HAS_TYPE, \
	HAS_NAME, \
	HAS_OPERATOR, \
	HAS_RETURN_TYPE, \
	HAS_PARAMETERS, \
	HAS_VARIADIC, \
	HAS_STATIC, \
	HAS_CV_QUALIFIER, \
	HAS_VIRTUAL, \
	HAS_EXPLICIT \
) \
CLASS_NAME::CLASS_NAME \
( \
	BOOST_PP_IIF(HAS_NAME, const std::string& name,) BOOST_PP_COMMA_IF(HAS_NAME) \
	BOOST_PP_IIF(HAS_OPERATOR, const overloadable_operator overloaded_operator,) BOOST_PP_COMMA_IF(HAS_OPERATOR) \
	BOOST_PP_IIF(HAS_RETURN_TYPE, const type_variant& return_type,) BOOST_PP_COMMA_IF(HAS_RETURN_TYPE) \
	BOOST_PP_IIF(HAS_PARAMETERS, function_parameter_list&& parameters,) BOOST_PP_COMMA_IF(HAS_PARAMETERS) \
	BOOST_PP_IIF(HAS_VARIADIC, const bool variadic,) BOOST_PP_COMMA_IF(HAS_VARIADIC) \
	const bool is_inline, \
	BOOST_PP_IIF(HAS_STATIC, const bool is_static,) BOOST_PP_COMMA_IF(HAS_STATIC) \
	BOOST_PP_IIF(HAS_CV_QUALIFIER, const bool is_const,) BOOST_PP_COMMA_IF(HAS_CV_QUALIFIER) \
	BOOST_PP_IIF(HAS_CV_QUALIFIER, const bool is_volatile,) BOOST_PP_COMMA_IF(HAS_CV_QUALIFIER) \
	BOOST_PP_IIF(HAS_VIRTUAL, const bool is_virtual,) BOOST_PP_COMMA_IF(HAS_VIRTUAL) \
	BOOST_PP_IIF(HAS_VIRTUAL, const bool is_pure,) BOOST_PP_COMMA_IF(HAS_VIRTUAL) \
	BOOST_PP_IIF(HAS_EXPLICIT, const bool is_explicit,) BOOST_PP_COMMA_IF(HAS_EXPLICIT) \
	void* const \
): \
	BOOST_PP_IIF(HAS_NAME, name_(name),) BOOST_PP_COMMA_IF(HAS_NAME) \
	BOOST_PP_IIF(HAS_OPERATOR, overloaded_operator_(overloaded_operator),) BOOST_PP_COMMA_IF(HAS_OPERATOR) \
	BOOST_PP_IIF(HAS_RETURN_TYPE, return_type_(return_type),) BOOST_PP_COMMA_IF(HAS_RETURN_TYPE) \
	BOOST_PP_IIF(HAS_PARAMETERS, parameters_(std::move(parameters)),) BOOST_PP_COMMA_IF(HAS_PARAMETERS) \
	BOOST_PP_IIF(HAS_VARIADIC, variadic_(variadic),) BOOST_PP_COMMA_IF(HAS_VARIADIC) \
	is_inline_(is_inline), \
	BOOST_PP_IIF(HAS_STATIC, is_static_(is_static),) BOOST_PP_COMMA_IF(HAS_STATIC) \
	BOOST_PP_IIF(HAS_CV_QUALIFIER, is_const_(is_const),) BOOST_PP_COMMA_IF(HAS_CV_QUALIFIER) \
	BOOST_PP_IIF(HAS_CV_QUALIFIER, is_volatile_(is_volatile),) BOOST_PP_COMMA_IF(HAS_CV_QUALIFIER) \
	BOOST_PP_IIF(HAS_VIRTUAL, is_virtual_(is_virtual),) BOOST_PP_COMMA_IF(HAS_VIRTUAL) \
	BOOST_PP_IIF(HAS_VIRTUAL, is_pure_(is_pure),) BOOST_PP_COMMA_IF(HAS_VIRTUAL) \
	BOOST_PP_IIF(HAS_EXPLICIT, is_explicit_(is_explicit),) BOOST_PP_COMMA_IF(HAS_EXPLICIT) \
	nothing_() \
{ \
} \
 \
BOOST_PP_IIF \
( \
	HAS_TYPE, \
	function_type \
	CLASS_NAME::type() const \
	{ \
		return \
			function_type \
			( \
				return_type_, \
				BOOST_PP_IIF(HAS_PARAMETERS, parameter_types(), std::vector<type_variant>()), \
				BOOST_PP_IIF(HAS_VARIADIC, variadic_, false), \
				BOOST_PP_IIF(HAS_CV_QUALIFIER, is_const_, false), \
				BOOST_PP_IIF(HAS_CV_QUALIFIER, is_volatile_, false) \
			) \
		; \
	}, \
) \
 \
BOOST_PP_IIF \
( \
	HAS_PARAMETERS, \
	std::vector<type_variant> \
	CLASS_NAME::parameter_types() const \
	{ \
		return get_parameter_types(parameters_); \
	} \
	, \
) \
 \
bool \
CLASS_NAME::defined() const \
{ \
	return body_.get(); \
} \
 \
std::shared_ptr<statement_block> \
CLASS_NAME::body() \
{ \
	return body_; \
} \
 \
std::shared_ptr<const statement_block> \
CLASS_NAME::body() const \
{ \
	return body_; \
} \
 \
void \
CLASS_NAME::body(std::shared_ptr<statement_block> b) \
{ \
	body_ = b; \
	body_->enclosing_declarative_region(shared_from_this()); \
} \
 \
bool \
CLASS_NAME::has_enclosing_declarative_region() const \
{ \
	return enclosing_declarative_region_; \
} \
 \
declarative_region_shared_ptr_variant \
CLASS_NAME::enclosing_declarative_region() const \
{ \
	if(enclosing_declarative_region_) \
		return utility::to_shared_ptr_variant(*enclosing_declarative_region_); \
	else \
		throw std::runtime_error("The declarative region is not set."); \
} \
 \
void \
CLASS_NAME::enclosing_declarative_region(const declarative_region_shared_ptr_variant& decl_region) \
{ \
	if(!enclosing_declarative_region_) \
		enclosing_declarative_region_ = utility::to_weak_ptr_variant(decl_region); \
	else \
		throw std::runtime_error("The declarative region is already set."); \
} \
 \
 \
 \
bool \
have_same_signature(const CLASS_NAME& lhs, const CLASS_NAME& rhs) \
{ \
	return \
		BOOST_PP_IIF(HAS_CV_QUALIFIER, lhs.is_const() == rhs.is_const() &&,) \
		BOOST_PP_IIF(HAS_CV_QUALIFIER, lhs.is_volatile() == rhs.is_volatile() &&,) \
		BOOST_PP_IIF(HAS_NAME, lhs.name() == rhs.name() &&,) \
		BOOST_PP_IIF(HAS_OPERATOR, lhs.overloaded_operator() == rhs.overloaded_operator() &&,) \
		BOOST_PP_IIF(HAS_RETURN_TYPE, lhs.return_type() == rhs.return_type() &&,) \
		BOOST_PP_IIF(HAS_PARAMETERS, lhs.parameter_types() == rhs.parameter_types() &&,) \
		BOOST_PP_IIF(HAS_VARIADIC, lhs.variadic() == rhs.variadic() &&,) \
		true \
	; \
}

namespace scalpel { namespace cpp { namespace semantic_entities
{

namespace
{
	std::vector<type_variant>
	get_parameter_types(const function_parameter_list& parameters)
	{
		std::vector<type_variant> parameter_types;

		for(auto i = parameters.begin(); i != parameters.end(); ++i)
		{
			const std::shared_ptr<const function_parameter>& param = *i;
			type_variant param_type = param->type();

			//remove cv-qualifiers
			if(cv_qualified_type* opt_cv_qualified_type = utility::get<cv_qualified_type>(&param_type))
			{
				param_type = opt_cv_qualified_type->qualified_type();
			}

			//array of T -> pointer to T
			if(array* opt_array = utility::get<array>(&param_type))
			{
				param_type = pointer(opt_array->qualified_type());
			}

			//TODO: function returning T -> pointer to function returning T

			//TODO: remove storage-class-specifiers

			parameter_types.push_back(param_type);
		}

		return parameter_types;
	}
}



//member functions
GENERATE_FUNCTION_DEFINITION(constructor,              0, 0, 0, 0, 1, 1, 0, 0, 0, 1)
GENERATE_FUNCTION_DEFINITION(destructor,               0, 0, 0, 0, 0, 0, 0, 0, 1, 0)
GENERATE_FUNCTION_DEFINITION(operator_member_function, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0)
GENERATE_FUNCTION_DEFINITION(conversion_function,      1, 0, 0, 1, 0, 0, 0, 1, 1, 1)
GENERATE_FUNCTION_DEFINITION(simple_member_function,   1, 1, 0, 1, 1, 1, 1, 1, 1, 0)

//free functions
GENERATE_FUNCTION_DEFINITION(operator_function,        1, 0, 1, 1, 1, 0, 1, 0, 0, 0)
GENERATE_FUNCTION_DEFINITION(simple_function,          1, 1, 0, 1, 1, 1, 1, 0, 0, 0)

}}} //namespace scalpel::cpp::semantic_entities

#undef GENERATE_FUNCTION_DEFINITION

