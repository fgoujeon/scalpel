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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_FUNCTIONS_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_FUNCTIONS_HPP

#include "overloadable_operator.hpp"
#include "function_parameter_list.hpp"
#include "variable.hpp"
#include "statement_block.hpp"
#include "declarative_region_variants.hpp"
#include "type_variants_fwd.hpp"
#include "detail/declarative_region_member_impl.hpp"
#include <scalpel/utility/empty.hpp>
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
	HAS_NAME, \
	HAS_OPERATOR, \
	HAS_RETURN_TYPE, \
	HAS_PARAMETERS, \
	HAS_STATIC, \
	HAS_CONST, \
	HAS_VOLATILE, \
	HAS_VIRTUAL, \
	HAS_EXPLICIT \
) \
class CLASS_NAME: \
	public std::enable_shared_from_this<CLASS_NAME> \
{ \
    public: \
		CLASS_NAME \
		( \
			BOOST_PP_IIF(HAS_NAME, const std::string& name,) BOOST_PP_COMMA_IF(HAS_NAME) \
			BOOST_PP_IIF(HAS_OPERATOR, const overloadable_operator overloaded_operator,) BOOST_PP_COMMA_IF(HAS_OPERATOR) \
			BOOST_PP_IIF(HAS_RETURN_TYPE, const type_variant& return_type,) BOOST_PP_COMMA_IF(HAS_RETURN_TYPE) \
			BOOST_PP_IIF(HAS_PARAMETERS, function_parameter_list&& parameters = function_parameter_list(),) BOOST_PP_COMMA_IF(HAS_PARAMETERS) \
			bool is_inline = false, \
			BOOST_PP_IIF(HAS_STATIC, bool is_static = false,) BOOST_PP_COMMA_IF(HAS_STATIC) \
			BOOST_PP_IIF(HAS_CONST, bool is_const = false,) BOOST_PP_COMMA_IF(HAS_CONST) \
			BOOST_PP_IIF(HAS_VOLATILE, bool is_volatile = false,) BOOST_PP_COMMA_IF(HAS_VOLATILE) \
			BOOST_PP_IIF(HAS_VIRTUAL, bool is_virtual = false,) BOOST_PP_COMMA_IF(HAS_VIRTUAL) \
			BOOST_PP_IIF(HAS_VIRTUAL, bool is_pure = false,) BOOST_PP_COMMA_IF(HAS_VIRTUAL) \
			BOOST_PP_IIF(HAS_EXPLICIT, bool is_explicit = false,) BOOST_PP_COMMA_IF(HAS_EXPLICIT) \
			void* const = 0 \
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
			overloaded_operator() const \
			{ \
				return overloaded_operator_; \
			}, \
		) \
 \
		BOOST_PP_IIF \
		( \
			HAS_RETURN_TYPE, \
			const type_variant& \
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
			HAS_CONST, \
			bool \
			is_const() const \
			{ \
				return is_const_; \
			}, \
		) \
 \
		BOOST_PP_IIF \
		( \
			HAS_VOLATILE, \
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
			overloadable_operator overloaded_operator_;, \
		) \
		BOOST_PP_IIF \
		( \
			HAS_RETURN_TYPE, \
			type_variant return_type_;, \
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
			HAS_CONST, \
			bool is_const_;, \
		) \
		BOOST_PP_IIF \
		( \
			HAS_VOLATILE, \
			bool is_volatile_;, \
		) \
		BOOST_PP_IIF \
		( \
			HAS_VIRTUAL, \
			bool is_virtual_; \
			bool is_pure_;, \
		) \
		BOOST_PP_IIF \
		( \
			HAS_EXPLICIT, \
			bool is_explicit_;, \
		) \
		std::shared_ptr<statement_block> body_; \
		const utility::empty nothing_; \
 \
		boost::optional<declarative_region_weak_ptr_variant> enclosing_declarative_region_; \
}; \
 \
bool \
have_same_signature(const CLASS_NAME& lhs, const CLASS_NAME& rhs);

namespace scalpel { namespace cpp { namespace semantic_entities
{

//member functions
GENERATE_FUNCTION_DECLARATION(constructor             , 0, 0, 0, 1, 0, 0, 0, 0, 1)
GENERATE_FUNCTION_DECLARATION(destructor              , 0, 0, 0, 0, 0, 0, 0, 1, 0)
GENERATE_FUNCTION_DECLARATION(operator_member_function, 0, 1, 1, 1, 0, 1, 1, 1, 0)
GENERATE_FUNCTION_DECLARATION(conversion_function     , 0, 0, 1, 0, 0, 1, 1, 1, 1)
GENERATE_FUNCTION_DECLARATION(simple_member_function  , 1, 0, 1, 1, 1, 1, 1, 1, 0)

//free functions
GENERATE_FUNCTION_DECLARATION(operator_function       , 0, 1, 1, 1, 1, 0, 0, 0, 0)
GENERATE_FUNCTION_DECLARATION(simple_function         , 1, 0, 1, 1, 1, 0, 0, 0, 0)

}}} //namespace scalpel::cpp::semantic_entities

#undef GENERATE_FUNCTION_DECLARATION

#endif

