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

#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/logical/or.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>

#define GENERATE_FUNCTION_DEFINITION(CLASS_NAME, HAS_NAME, HAS_OPERATOR, HAS_RETURN_TYPE, HAS_PARAMETERS, HAS_STATIC, HAS_EXPLICIT) \
CLASS_NAME::CLASS_NAME \
( \
	BOOST_PP_IIF(HAS_NAME, const std::string& name,) BOOST_PP_COMMA_IF(HAS_NAME) \
	BOOST_PP_IIF(HAS_OPERATOR, const overloadable_operator op,) BOOST_PP_COMMA_IF(HAS_OPERATOR) \
	BOOST_PP_IIF(HAS_RETURN_TYPE, const type_shared_ptr_variant& return_type,) BOOST_PP_COMMA_IF(HAS_RETURN_TYPE) \
	BOOST_PP_IIF(HAS_PARAMETERS, function_parameter_list&& parameters,) BOOST_PP_COMMA_IF(HAS_PARAMETERS) \
	bool is_inline BOOST_PP_COMMA_IF(BOOST_PP_OR(HAS_STATIC, HAS_EXPLICIT)) \
	BOOST_PP_IIF(HAS_STATIC, bool is_static,) \
	BOOST_PP_IIF(HAS_EXPLICIT, bool is_explicit,) \
): \
	BOOST_PP_IIF(HAS_NAME, name_(name),) BOOST_PP_COMMA_IF(HAS_NAME) \
	BOOST_PP_IIF(HAS_OPERATOR, op_(op),) BOOST_PP_COMMA_IF(HAS_OPERATOR) \
	BOOST_PP_IIF(HAS_RETURN_TYPE, return_type_(return_type),) BOOST_PP_COMMA_IF(HAS_RETURN_TYPE) \
	BOOST_PP_IIF(HAS_PARAMETERS, parameters_(std::move(parameters)),) BOOST_PP_COMMA_IF(HAS_PARAMETERS) \
	is_inline_(is_inline) BOOST_PP_COMMA_IF(BOOST_PP_OR(HAS_STATIC, HAS_EXPLICIT)) \
	BOOST_PP_IIF(HAS_STATIC, is_static_(is_static),) \
	BOOST_PP_IIF(HAS_EXPLICIT, is_explicit_(is_explicit),) \
{ \
} \
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
operator==(const CLASS_NAME& lhs, const CLASS_NAME& rhs) \
{ \
	return \
		lhs.is_inline() == rhs.is_inline() && \
		BOOST_PP_IIF(HAS_STATIC, lhs.is_static() == rhs.is_static() &&,) \
		BOOST_PP_IIF(HAS_EXPLICIT, lhs.is_explicit() == rhs.is_explicit() &&,) \
		have_same_signature(lhs, rhs) && \
		utility::are_pointed_objects_equal(lhs.body(), rhs.body()) \
	; \
} \
 \
bool \
operator!=(const CLASS_NAME& lhs, const CLASS_NAME& rhs) \
{ \
	return !operator==(lhs, rhs); \
} \
 \
bool \
have_same_signature(const CLASS_NAME& lhs, const CLASS_NAME& rhs) \
{ \
	return \
		BOOST_PP_IIF(HAS_NAME, lhs.name() == rhs.name() &&,) \
		BOOST_PP_IIF(HAS_OPERATOR, lhs.get_operator() == rhs.get_operator() &&,) \
		BOOST_PP_IIF(HAS_RETURN_TYPE, utility::are_pointed_objects_equal(lhs.return_type(), rhs.return_type()) &&,) \
		BOOST_PP_IIF(HAS_PARAMETERS, have_same_types(lhs.parameters(), rhs.parameters()) &&,) \
		true \
	; \
}

