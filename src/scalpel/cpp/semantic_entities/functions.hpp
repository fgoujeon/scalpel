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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_FUNCTIONS_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_FUNCTIONS_HPP

#include "function_type.hpp"
#include "overloadable_operator.hpp"
#include "function_parameter_list.hpp"
#include "variable.hpp"
#include "statement_block.hpp"
#include "declarative_regions.hpp"
#include "type_fwd.hpp"
#include "impl/detail/declarative_region_member_impl.hpp"
#include "macros/detail/declarative_region_member_impl.hpp"
#include <boost/optional.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/logical/or.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <string>
#include <list>
#include <memory>

#define GENERATE_FUNCTION_DECLARATION( \
	CLASS_NAME, \
	IS_MEMBER, \
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
class CLASS_NAME \
{ \
    public: \
		CLASS_NAME \
		( \
			BOOST_PP_IIF(HAS_NAME, const std::string& name,) BOOST_PP_COMMA_IF(HAS_NAME) \
			BOOST_PP_IIF(HAS_OPERATOR, const overloadable_operator overloaded_operator,) BOOST_PP_COMMA_IF(HAS_OPERATOR) \
			BOOST_PP_IIF(HAS_RETURN_TYPE, const type_t& return_type,) BOOST_PP_COMMA_IF(HAS_RETURN_TYPE) \
			BOOST_PP_IIF(HAS_PARAMETERS, function_parameter_list&& parameters,) BOOST_PP_COMMA_IF(HAS_PARAMETERS) \
			BOOST_PP_IIF(HAS_VARIADIC, const bool variadic,) BOOST_PP_COMMA_IF(HAS_VARIADIC) \
			BOOST_PP_IIF(IS_MEMBER, const member_access access,) BOOST_PP_COMMA_IF(IS_MEMBER) \
			BOOST_PP_IIF(HAS_CV_QUALIFIER, const bool is_const,) BOOST_PP_COMMA_IF(HAS_CV_QUALIFIER) \
			BOOST_PP_IIF(HAS_CV_QUALIFIER, const bool is_volatile,) BOOST_PP_COMMA_IF(HAS_CV_QUALIFIER) \
			BOOST_PP_IIF(HAS_STATIC, const bool is_static,) BOOST_PP_COMMA_IF(HAS_STATIC) \
			BOOST_PP_IIF(HAS_EXPLICIT, const bool is_explicit,) BOOST_PP_COMMA_IF(HAS_EXPLICIT) \
			BOOST_PP_IIF(HAS_VIRTUAL, const bool is_virtual,) BOOST_PP_COMMA_IF(HAS_VIRTUAL) \
			BOOST_PP_IIF(HAS_VIRTUAL, const bool is_pure,) BOOST_PP_COMMA_IF(HAS_VIRTUAL) \
			const bool is_inline \
		); \
 \
		CLASS_NAME(const CLASS_NAME&) = delete; \
 \
		CLASS_NAME& \
		operator=(const CLASS_NAME&) = delete; \
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
			overloaded_operator() const \
			{ \
				return overloaded_operator_; \
			}, \
		) \
 \
		BOOST_PP_IIF \
		( \
			HAS_RETURN_TYPE, \
			const type_t& \
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
			} \
 \
			std::vector<type_t> \
			parameter_types() const; \
			, \
		) \
 \
		BOOST_PP_IIF \
		( \
			HAS_VARIADIC, \
			bool \
			variadic() const \
			{ \
				return variadic_; \
			}, \
		) \
 \
		BOOST_PP_IIF \
		( \
			IS_MEMBER, \
			member_access \
			access() const \
			{ \
				return access_; \
			}, \
		) \
 \
		BOOST_PP_IIF \
		( \
			HAS_TYPE, \
			function_type \
			type() const;, \
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
			HAS_CV_QUALIFIER, \
			bool \
			is_const() const \
			{ \
				return is_const_; \
			}, \
		) \
 \
		BOOST_PP_IIF \
		( \
			HAS_CV_QUALIFIER, \
			bool \
			is_volatile() const \
			{ \
				return is_volatile_; \
			}, \
		) \
 \
		BOOST_PP_IIF \
		( \
			HAS_VIRTUAL, \
			bool \
			is_virtual() const \
			{ \
				return is_virtual_; \
			} \
 \
			bool \
			is_pure() const \
			{ \
				return is_pure_; \
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
		statement_block& \
		body(); \
 \
		const statement_block& \
		body() const; \
 \
		void \
		body(std::unique_ptr<statement_block>&& b); \
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
			overloadable_operator overloaded_operator_;, \
		) \
		BOOST_PP_IIF \
		( \
			HAS_RETURN_TYPE, \
			type_t return_type_;, \
		) \
		BOOST_PP_IIF \
		( \
			HAS_PARAMETERS, \
			function_parameter_list parameters_;, \
		) \
		BOOST_PP_IIF \
		( \
			HAS_VARIADIC, \
			bool variadic_;, \
		) \
		BOOST_PP_IIF \
		( \
			IS_MEMBER, \
			member_access access_;, \
		) \
		BOOST_PP_IIF \
		( \
			HAS_CV_QUALIFIER, \
			bool is_const_;, \
		) \
		BOOST_PP_IIF \
		( \
			HAS_CV_QUALIFIER, \
			bool is_volatile_;, \
		) \
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
		BOOST_PP_IIF \
		( \
			HAS_VIRTUAL, \
			bool is_virtual_; \
			bool is_pure_;, \
		) \
		bool is_inline_; \
		std::unique_ptr<statement_block> body_; \
 \
		boost::optional<declarative_region_t> enclosing_declarative_region_; \
 \
		BOOST_PP_IIF \
		( \
			IS_MEMBER, \
			DECLARATIVE_REGION_MEMBER_IMPL(member_function_declarative_region_member_impl_t), \
			DECLARATIVE_REGION_MEMBER_IMPL(function_declarative_region_member_impl_t) \
		) \
}; \
 \
bool \
have_same_signature(const CLASS_NAME& lhs, const CLASS_NAME& rhs);

namespace scalpel { namespace cpp { namespace semantic_entities
{

typedef
	impl::detail::declarative_region_member_impl<namespace_, unnamed_namespace, linked_namespace, linked_unnamed_namespace>
	function_declarative_region_member_impl_t
;

typedef
	impl::detail::declarative_region_member_impl<class_, member_class, union_, member_union, anonymous_union, anonymous_member_union>
	member_function_declarative_region_member_impl_t
;

//member functions
GENERATE_FUNCTION_DECLARATION(constructor,              1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1)
GENERATE_FUNCTION_DECLARATION(destructor,               1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0)
GENERATE_FUNCTION_DECLARATION(operator_member_function, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0)
GENERATE_FUNCTION_DECLARATION(conversion_function,      1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1)
GENERATE_FUNCTION_DECLARATION(simple_member_function,   1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0)

//free functions
GENERATE_FUNCTION_DECLARATION(operator_function,        0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0)
GENERATE_FUNCTION_DECLARATION(simple_function,          0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0)

}}} //namespace scalpel::cpp::semantic_entities

#undef GENERATE_FUNCTION_DECLARATION

#include "macros/detail/declarative_region_member_impl_undef.hpp"

#endif

