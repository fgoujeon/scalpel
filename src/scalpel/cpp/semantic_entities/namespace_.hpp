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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_NAMESPACE_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_NAMESPACE_HPP

#include "declarative_region_variants.hpp"
#include "namespace_alias.hpp"
#include "class_.hpp"
#include "enum_.hpp"
#include "functions.hpp"
#include "typedef_.hpp"
#include "variable.hpp"
#include "macros/detail/declarative_region_member_impl.hpp"
#include <scalpel/utility/unique_ptr_vector.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <string>
#include <vector>
#include <memory>

#define NAME_PROPERTY \
	public: \
		const std::string& \
		name() const \
		{ \
			return name_; \
		} \
 \
	private: \
		std::string name_;



#define MEMBERS_OF_TYPE(TYPE, NAME) \
	public: \
		typedef utility::unique_ptr_vector<TYPE> NAME##_t; \
 \
		NAME##_t::range \
		NAME(); \
 \
		const NAME##_t& \
		NAME() const; \
 \
		void \
		add_member(std::unique_ptr<TYPE>&& member); \
 \
	private: \
		NAME##_t NAME##_;



#define MEMBER_OF_TYPE(TYPE, NAME) \
	public: \
		TYPE* \
		get_##NAME() \
		{ \
			return NAME##_.get(); \
		} \
 \
		const TYPE* \
		get_##NAME() const \
		{ \
			return NAME##_.get(); \
		} \
 \
		void \
		set_##NAME(std::unique_ptr<TYPE>&& member); \
 \
	private: \
		std::unique_ptr<TYPE> NAME##_;



#define USING_DIRECTIVE_NAMESPACES \
	public: \
		typedef std::vector<namespace_*> namespace_ptrs_t; \
 \
		const namespace_ptrs_t& \
		using_directive_namespaces() const \
		{ \
			return using_directive_namespaces_; \
		} \
 \
		void \
		add_using_directive_namespace(namespace_& n) \
		{ \
			using_directive_namespaces_.push_back(&n); \
		} \
 \
	private: \
		namespace_ptrs_t using_directive_namespaces_;



#define USING_DECLARATION_MEMBERS_OF_TYPE(TYPE, NAME) \
	public: \
		typedef std::vector<TYPE*> using_declaration_##NAME##_t; \
 \
		using_declaration_##NAME##_t& \
		using_declaration_##NAME() \
		{ \
			return using_declaration_##NAME##_; \
		} \
 \
		void \
		add_using_declaration_member(TYPE& member) \
		{ \
			using_declaration_##NAME##_.push_back(&member); \
		} \
 \
	private: \
		using_declaration_##NAME##_t using_declaration_##NAME##_;



#define GENERATE_NAMESPACE_DECLARATION( \
	CLASS_NAME, \
	NAMESPACE_TYPE, \
	UNNAMED_NAMESPACE_TYPE, \
	DECLARATIVE_REGION_MEMBER_IMPL_T, \
	IS_NAMED, \
	CAN_HAVE_MULTIPLE_UNNAMED_NAMESPACES, \
	HAS_NAMESPACE_ALIASES, \
	HAS_USING_DIRECTIVE_NAMESPACES \
) \
struct CLASS_NAME \
{ \
	CLASS_NAME(); \
 \
	BOOST_PP_IIF \
	( \
		IS_NAMED, \
		explicit CLASS_NAME(const std::string& name);, \
	) \
 \
	CLASS_NAME(const CLASS_NAME&) = delete; \
 \
	const CLASS_NAME& \
	operator=(const CLASS_NAME&) = delete; \
 \
	BOOST_PP_IIF(IS_NAMED, NAME_PROPERTY,) \
 \
	MEMBERS_OF_TYPE(NAMESPACE_TYPE, namespaces) \
	BOOST_PP_IIF \
	( \
		CAN_HAVE_MULTIPLE_UNNAMED_NAMESPACES, \
		MEMBERS_OF_TYPE(UNNAMED_NAMESPACE_TYPE, unnamed_namespaces), \
		MEMBER_OF_TYPE(UNNAMED_NAMESPACE_TYPE, unnamed_namespace) \
	) \
	BOOST_PP_IIF \
	( \
		HAS_NAMESPACE_ALIASES, \
		MEMBERS_OF_TYPE(namespace_alias, namespace_aliases), \
	) \
	MEMBERS_OF_TYPE(class_, classes) \
	MEMBERS_OF_TYPE(enum_, enums) \
	MEMBERS_OF_TYPE(typedef_, typedefs) \
	MEMBERS_OF_TYPE(simple_function, simple_functions) \
	MEMBERS_OF_TYPE(operator_function, operator_functions) \
	MEMBERS_OF_TYPE(variable, variables) \
 \
	BOOST_PP_IIF \
	( \
		HAS_USING_DIRECTIVE_NAMESPACES, \
		USING_DIRECTIVE_NAMESPACES, \
	) \
	USING_DECLARATION_MEMBERS_OF_TYPE(class_, classes) \
	USING_DECLARATION_MEMBERS_OF_TYPE(variable, variables) \
 \
	DECLARATIVE_REGION_MEMBER_IMPL(DECLARATIVE_REGION_MEMBER_IMPL_T) \
};

namespace scalpel { namespace cpp { namespace semantic_entities
{

class namespace_;
class unnamed_namespace;
class linked_namespace;
class linked_unnamed_namespace;

typedef
	impl::detail::declarative_region_member_impl<namespace_, unnamed_namespace>
	namespace_declarative_region_member_impl_t
;

typedef
	impl::detail::declarative_region_member_impl<linked_namespace, linked_unnamed_namespace>
	linked_namespace_declarative_region_member_impl_t
;

GENERATE_NAMESPACE_DECLARATION(namespace_, namespace_, unnamed_namespace, namespace_declarative_region_member_impl_t, 1, 0, 1, 1)
GENERATE_NAMESPACE_DECLARATION(unnamed_namespace, namespace_, unnamed_namespace, namespace_declarative_region_member_impl_t, 0, 0, 1, 1)
GENERATE_NAMESPACE_DECLARATION(linked_unnamed_namespace, linked_namespace, linked_unnamed_namespace, linked_namespace_declarative_region_member_impl_t, 0, 0, 0, 0)
GENERATE_NAMESPACE_DECLARATION(linked_namespace, linked_namespace, linked_unnamed_namespace, linked_namespace_declarative_region_member_impl_t, 1, 1, 0, 0)

}}} //namespace scalpel::cpp::semantic_entities

#undef NAME_PROPERTY
#undef MEMBERS_OF_TYPE
#undef MEMBER_OF_TYPE
#undef USING_DIRECTIVE_NAMESPACES
#undef USING_DECLARATION_MEMBERS_OF_TYPE
#undef GENERATE_NAMESPACE_DECLARATION

#include "macros/detail/declarative_region_member_impl_undef.hpp"

#endif

