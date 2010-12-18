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
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#define GENERATE_FUNCTION_DECLARATION(CLASS_NAME, HAS_NAME, HAS_OPERATOR, HAS_RETURN_TYPE, HAS_PARAMETERS, HAS_STATIC, HAS_EXPLICIT) \
class CLASS_NAME: \
	public std::enable_shared_from_this<CLASS_NAME> \
{ \
    public: \
		CLASS_NAME \
		( \
			BOOST_PP_IIF(HAS_NAME, const std::string& name,) BOOST_PP_COMMA_IF(HAS_NAME) \
			BOOST_PP_IIF(HAS_OPERATOR, const overloadable_operator op,) BOOST_PP_COMMA_IF(HAS_OPERATOR) \
			BOOST_PP_IIF(HAS_RETURN_TYPE, const type_shared_ptr_variant& return_type,) BOOST_PP_COMMA_IF(HAS_RETURN_TYPE) \
			BOOST_PP_IIF(HAS_PARAMETERS, function_parameter_list&& parameters = function_parameter_list(),) BOOST_PP_COMMA_IF(HAS_PARAMETERS) \
			bool is_inline = false BOOST_PP_COMMA_IF(BOOST_PP_OR(HAS_STATIC, HAS_EXPLICIT)) \
			BOOST_PP_IIF(HAS_STATIC, bool is_static = false,) \
			BOOST_PP_IIF(HAS_EXPLICIT, bool is_explicit = false,) \
		); \
 \
		BOOST_PP_IIF \
		( \
			HAS_NAME, \
			const std::string& \
			name() const \
			{ \
				return name_; \
			}, \
		) \
 \
		BOOST_PP_IIF \
		( \
			HAS_OPERATOR, \
			overloadable_operator \
			get_operator() const \
			{ \
				return op_; \
			}, \
		) \
 \
		BOOST_PP_IIF \
		( \
			HAS_RETURN_TYPE, \
			const type_shared_ptr_variant& \
			return_type() const \
			{ \
				return return_type_; \
			}, \
		) \
 \
		BOOST_PP_IIF \
		( \
			HAS_PARAMETERS, \
			const function_parameter_list& \
			parameters() const \
			{ \
				return parameters_; \
			}, \
		) \
 \
		bool \
		is_inline() const \
		{ \
			return is_inline_; \
		} \
 \
		BOOST_PP_IIF \
		( \
			HAS_STATIC, \
			bool \
			is_static() const \
			{ \
				return is_static_; \
			}, \
		) \
 \
		BOOST_PP_IIF \
		( \
			HAS_EXPLICIT, \
			bool \
			is_explicit() const \
			{ \
				return is_explicit_; \
			}, \
		) \
 \
		bool \
		defined() const; \
 \
		std::shared_ptr<statement_block> \
		body(); \
 \
		std::shared_ptr<const statement_block> \
		body() const; \
 \
		void \
		body(std::shared_ptr<statement_block> b); \
 \
		bool \
		has_enclosing_declarative_region() const; \
 \
		declarative_region_shared_ptr_variant \
		enclosing_declarative_region() const; \
 \
		void \
		enclosing_declarative_region(const declarative_region_shared_ptr_variant& enclosing_declarative_region); \
 \
    private: \
		BOOST_PP_IIF \
		( \
			HAS_NAME, \
			std::string name_;, \
		) \
		BOOST_PP_IIF \
		( \
			HAS_OPERATOR, \
			overloadable_operator op_;, \
		) \
		BOOST_PP_IIF \
		( \
			HAS_RETURN_TYPE, \
			type_shared_ptr_variant return_type_;, \
		) \
		BOOST_PP_IIF \
		( \
			HAS_PARAMETERS, \
			function_parameter_list parameters_;, \
		) \
		bool is_inline_; \
		BOOST_PP_IIF \
		( \
			HAS_STATIC, \
			bool is_static_;, \
		) \
		BOOST_PP_IIF \
		( \
			HAS_EXPLICIT, \
			bool is_explicit_;, \
		) \
		std::shared_ptr<statement_block> body_; \
 \
		boost::optional<declarative_region_weak_ptr_variant> enclosing_declarative_region_; \
}; \
 \
bool \
operator==(const CLASS_NAME& lhs, const CLASS_NAME& rhs); \
 \
bool \
operator!=(const CLASS_NAME& lhs, const CLASS_NAME& rhs); \
 \
bool \
have_same_signature(const CLASS_NAME& lhs, const CLASS_NAME& rhs);

