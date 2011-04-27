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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_VARIABLE_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_VARIABLE_HPP

#include "type_variant.hpp"
#include "impl/detail/declarative_region_member_impl.hpp"
#include "macros/detail/declarative_region_member_impl.hpp"
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <string>
#include <memory>

#define GENERATE_VARIABLE_DECLARATION( \
	CLASS_NAME, \
	IS_MEMBER, \
	HAS_STATIC, \
	HAS_SIZE \
) \
class CLASS_NAME \
{ \
	public: \
		CLASS_NAME \
		( \
			const std::string& name, \
			const type_variant& type BOOST_PP_COMMA_IF(HAS_SIZE) \
			BOOST_PP_IIF(HAS_SIZE, unsigned int size,) BOOST_PP_COMMA_IF(HAS_STATIC) \
			BOOST_PP_IIF(HAS_STATIC, bool is_static = false,) BOOST_PP_COMMA_IF(IS_MEMBER) \
			BOOST_PP_IIF(IS_MEMBER, const bool is_mutable = false,) BOOST_PP_COMMA_IF(IS_MEMBER) \
			BOOST_PP_IIF(IS_MEMBER, const member_access access = member_access::PUBLIC,) \
		); \
 \
		CLASS_NAME(const CLASS_NAME&) = delete; \
 \
		CLASS_NAME& \
		operator=(const CLASS_NAME&) = delete; \
 \
		const type_variant& \
		type() const \
		{ \
			return type_; \
		} \
 \
		const std::string& \
		name() const \
		{ \
			return name_; \
		} \
 \
		BOOST_PP_IIF \
		( \
			HAS_SIZE, \
			unsigned int \
			size() const \
			{ \
				return size_; \
			}, \
		) \
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
			IS_MEMBER, \
			bool \
			is_mutable() const \
			{ \
				return is_mutable_; \
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
	private: \
		type_variant type_; \
		std::string name_; \
		BOOST_PP_IIF \
		( \
			HAS_SIZE, \
			unsigned int size_;, \
		) \
		BOOST_PP_IIF \
		( \
			HAS_STATIC, \
			bool is_static_;, \
		) \
		BOOST_PP_IIF \
		( \
			IS_MEMBER, \
			bool is_mutable_;, \
		) \
		BOOST_PP_IIF \
		( \
			IS_MEMBER, \
			member_access access_;, \
		) \
 \
		BOOST_PP_IIF \
		( \
			IS_MEMBER, \
			DECLARATIVE_REGION_MEMBER_IMPL(member_variable_declarative_region_member_impl_t), \
			DECLARATIVE_REGION_MEMBER_IMPL(variable_declarative_region_member_impl_t) \
		) \
};

namespace scalpel { namespace cpp { namespace semantic_entities
{

typedef
	impl::detail::declarative_region_member_impl<namespace_, unnamed_namespace, linked_namespace, linked_unnamed_namespace>
	variable_declarative_region_member_impl_t
;

typedef
	impl::detail::declarative_region_member_impl<class_, member_class, union_, member_union>
	member_variable_declarative_region_member_impl_t
;

GENERATE_VARIABLE_DECLARATION(variable, 0, 1, 0)
GENERATE_VARIABLE_DECLARATION(member_variable, 1, 1, 0)
GENERATE_VARIABLE_DECLARATION(bit_field, 1, 0, 1)

}}} //namespace scalpel::cpp::semantic_entities

#undef GENERATE_VARIABLE_DECLARATION

#include "macros/detail/declarative_region_member_impl_undef.hpp"

#endif

