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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_ENUM_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_ENUM_HPP

#include "enum_constant.hpp"
#include "member_access.hpp"
#include "impl/detail/declarative_region_member_impl.hpp"
#include "macros/detail/declarative_region_member_impl.hpp"
#include <scalpel/utility/unique_ptr_vector.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <string>

#define GENERATE_ENUM_DECLARATION(CLASS_NAME, IS_MEMBER) \
template<typename UnderlyingType> \
class CLASS_NAME \
{ \
	public: \
		typedef enum_constant<UnderlyingType> constant; \
		typedef utility::unique_ptr_vector<constant> constants_t; \
 \
		BOOST_PP_IIF \
		( \
			IS_MEMBER, \
			CLASS_NAME(const std::string& name, const member_access access);, \
			explicit CLASS_NAME(const std::string& name); \
		) \
 \
        CLASS_NAME(const CLASS_NAME&) = delete; \
 \
        CLASS_NAME(CLASS_NAME&& rhs); \
 \
        CLASS_NAME& \
		operator=(const CLASS_NAME&) = delete; \
 \
        CLASS_NAME& \
		operator=(CLASS_NAME&& rhs); \
 \
		const std::string& \
		name() const \
		{ \
			return name_; \
		} \
 \
		typename constants_t::range \
		constants() \
		{ \
			return constants_; \
		} \
 \
		const constants_t& \
		constants() const \
		{ \
			return constants_; \
		} \
 \
		void \
		add(std::unique_ptr<constant>&& c) \
		{ \
			constants_.push_back(std::move(c)); \
		} \
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
        std::string name_; \
		constants_t constants_; \
		BOOST_PP_IIF \
		( \
			IS_MEMBER, \
			member_access access_;, \
		) \
 \
		BOOST_PP_IIF \
		( \
			IS_MEMBER, \
			DECLARATIVE_REGION_MEMBER_IMPL(member_enum_declarative_region_member_impl_t), \
			DECLARATIVE_REGION_MEMBER_IMPL(enum_declarative_region_member_impl_t) \
		) \
};

namespace scalpel { namespace cpp { namespace semantic_entities
{

class namespace_;
class unnamed_namespace;
class linked_namespace;
class linked_unnamed_namespace;
class class_;
class member_class;
class union_;
class member_union;
class anonymous_union;
class anonymous_member_union;

typedef
	impl::detail::declarative_region_member_impl<namespace_, unnamed_namespace, linked_namespace, linked_unnamed_namespace>
	enum_declarative_region_member_impl_t
;

typedef
	impl::detail::declarative_region_member_impl<class_, member_class, union_, member_union, anonymous_union, anonymous_member_union>
	member_enum_declarative_region_member_impl_t
;

GENERATE_ENUM_DECLARATION(basic_enum, 0)
GENERATE_ENUM_DECLARATION(basic_member_enum, 1)

typedef
	utility::variant
	<
		basic_enum<int>,
		basic_enum<unsigned int>,
		basic_enum<long int>,
		basic_enum<long unsigned int>
	>
	enum_typedef
;
typedef
	utility::variant
	<
		basic_member_enum<int>,
		basic_member_enum<unsigned int>,
		basic_member_enum<long int>,
		basic_member_enum<long unsigned int>
	>
	member_enum_typedef
;

struct enum_t: enum_typedef
{
	template<typename U>
	enum_t
	(
		U&& value,
		typename boost::disable_if<boost::is_const<U>>::type* = 0,
		typename boost::disable_if<boost::is_reference<U>>::type* = 0,
		typename boost::disable_if<boost::is_same<U, enum_typedef>>::type* = 0
	): enum_typedef(std::move(value))
	{
	}
};

struct member_enum_t: member_enum_typedef
{
	template<typename U>
	member_enum_t
	(
		U&& value,
		typename boost::disable_if<boost::is_const<U>>::type* = 0,
		typename boost::disable_if<boost::is_reference<U>>::type* = 0,
		typename boost::disable_if<boost::is_same<U, member_enum_typedef>>::type* = 0
	): member_enum_typedef(std::move(value))
	{
	}
};

}}} //namespace scalpel::cpp::semantic_entities

#include "macros/detail/declarative_region_member_impl_undef.hpp"

#include "enum.ipp"

#endif

