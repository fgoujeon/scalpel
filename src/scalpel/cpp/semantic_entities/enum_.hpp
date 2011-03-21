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
class CLASS_NAME \
{ \
	public: \
		typedef utility::unique_ptr_vector<enum_constant> constants_t; \
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
        CLASS_NAME& \
		operator=(const CLASS_NAME&) = delete; \
 \
		const std::string& \
		name() const \
		{ \
			return name_; \
		} \
 \
		const constants_t& \
		constants() const \
		{ \
			return constants_; \
		} \
 \
		void \
		add(std::unique_ptr<enum_constant>&& c) \
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
			DECLARATIVE_REGION_MEMBER_IMPL(impl::detail::declarative_region_member_impl<namespace_>) \
		) \
};

namespace scalpel { namespace cpp { namespace semantic_entities
{

class namespace_;
class class_;
class member_class;

typedef
	impl::detail::declarative_region_member_impl<class_, member_class>
	member_enum_declarative_region_member_impl_t
;

GENERATE_ENUM_DECLARATION(enum_, 0)
GENERATE_ENUM_DECLARATION(member_enum, 1)

}}} //namespace scalpel::cpp::semantic_entities

#include "macros/detail/declarative_region_member_impl_undef.hpp"

#endif

