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
class CLASS_NAME \
{ \
	public: \
		typedef std::vector<namespace_*> namespace_ptrs_t; \
 \
		typedef utility::unique_ptr_vector<NAMESPACE_TYPE> namespaces_t; \
		BOOST_PP_IIF \
		( \
			CAN_HAVE_MULTIPLE_UNNAMED_NAMESPACES, \
			typedef utility::unique_ptr_vector<UNNAMED_NAMESPACE_TYPE> unnamed_namespaces_t;, \
		) \
		typedef utility::unique_ptr_vector<namespace_alias> namespace_aliases_t; \
		typedef utility::unique_ptr_vector<class_> classes_t; \
		typedef utility::unique_ptr_vector<enum_> enums_t; \
		typedef utility::unique_ptr_vector<typedef_> typedefs_t; \
		typedef utility::unique_ptr_vector<simple_function> simple_functions_t; \
		typedef utility::unique_ptr_vector<operator_function> operator_functions_t; \
		typedef utility::unique_ptr_vector<variable> variables_t; \
 \
		typedef std::vector<class_*> using_declaration_classes_t; \
		typedef std::vector<variable*> using_declaration_variables_t; \
 \
	public: \
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
		BOOST_PP_IIF \
		( \
			IS_NAMED, \
			const std::string& \
			name() const \
			{ \
				return name_; \
			}, \
		) \
 \
		namespaces_t::range \
		namespaces(); \
 \
		const namespaces_t& \
		namespaces() const; \
 \
		BOOST_PP_IIF \
		( \
			CAN_HAVE_MULTIPLE_UNNAMED_NAMESPACES, \
 \
			unnamed_namespaces_t::range \
			unnamed_namespaces() \
			{ \
				return unnamed_namespaces_; \
			}, \
 \
			UNNAMED_NAMESPACE_TYPE* \
			get_unnamed_namespace() \
			{ \
				return unnamed_namespace_.get(); \
			} \
		) \
 \
		BOOST_PP_IIF \
		( \
			CAN_HAVE_MULTIPLE_UNNAMED_NAMESPACES, \
 \
			const unnamed_namespaces_t& \
			unnamed_namespaces() const \
			{ \
				return unnamed_namespaces_; \
			}, \
 \
			const UNNAMED_NAMESPACE_TYPE* \
			get_unnamed_namespace() const \
			{ \
				return unnamed_namespace_.get(); \
			} \
		) \
 \
		classes_t::range \
		classes(); \
 \
		const classes_t& \
		classes() const; \
 \
		enums_t::range \
		enums(); \
 \
		const enums_t& \
		enums() const; \
 \
		typedefs_t::range \
		typedefs(); \
 \
		const typedefs_t& \
		typedefs() const; \
 \
		simple_functions_t::range \
		simple_functions(); \
 \
		const simple_functions_t& \
		simple_functions() const; \
 \
		operator_functions_t::range \
		operator_functions(); \
 \
		const operator_functions_t& \
		operator_functions() const; \
 \
		variables_t::range \
		variables(); \
 \
		const variables_t& \
		variables() const; \
 \
		using_declaration_classes_t& \
		using_declaration_classes() \
		{ \
			return using_declaration_classes_; \
		} \
 \
		using_declaration_variables_t& \
		using_declaration_variables() \
		{ \
			return using_declaration_variables_; \
		} \
 \
		BOOST_PP_IIF \
		( \
			HAS_NAMESPACE_ALIASES, \
 \
			namespace_aliases_t::range \
			namespace_aliases() \
			{ \
				return namespace_aliases_; \
			} \
 \
			const namespace_aliases_t& \
			namespace_aliases() const \
			{ \
				return namespace_aliases_; \
			}, \
		) \
 \
		BOOST_PP_IIF \
		( \
			HAS_USING_DIRECTIVE_NAMESPACES, \
			const namespace_ptrs_t& \
			using_directive_namespaces() const \
			{ \
				return using_directive_namespaces_; \
			}, \
		) \
 \
		BOOST_PP_IIF \
		( \
			HAS_NAMESPACE_ALIASES, \
			void \
			add_member(std::unique_ptr<namespace_alias>&& member);, \
		) \
 \
		void \
		add_member(std::unique_ptr<NAMESPACE_TYPE>&& member); \
 \
		BOOST_PP_IIF \
		( \
			CAN_HAVE_MULTIPLE_UNNAMED_NAMESPACES, \
 \
			void \
			add_member(std::unique_ptr<UNNAMED_NAMESPACE_TYPE>&& member);, \
 \
			void \
			set_unnamed_namespace(std::unique_ptr<UNNAMED_NAMESPACE_TYPE>&& member); \
		) \
 \
		void \
		add_member(std::unique_ptr<class_>&& member); \
 \
		void \
		add_member(std::unique_ptr<enum_>&& member); \
 \
		void \
		add_member(std::unique_ptr<typedef_>&& member); \
 \
		void \
		add_member(std::unique_ptr<simple_function>&& member); \
 \
		void \
		add_member(std::unique_ptr<operator_function>&& member); \
 \
		void \
		add_member(std::unique_ptr<variable>&& member); \
 \
		BOOST_PP_IIF \
		( \
			HAS_USING_DIRECTIVE_NAMESPACES, \
			void \
			add_using_directive_namespace(namespace_& n);, \
		) \
 \
		void \
		add_using_declaration_member(class_& member); \
 \
		void \
		add_using_declaration_member(variable& member); \
 \
	private: \
		BOOST_PP_IIF \
		( \
			IS_NAMED, \
			std::string name_;, \
		) \
 \
		namespace_aliases_t namespace_aliases_; \
		namespaces_t namespaces_; \
		BOOST_PP_IIF \
		( \
			CAN_HAVE_MULTIPLE_UNNAMED_NAMESPACES, \
			unnamed_namespaces_t unnamed_namespaces_;, \
			std::unique_ptr<UNNAMED_NAMESPACE_TYPE> unnamed_namespace_; \
		) \
		classes_t classes_; \
		enums_t enums_; \
		typedefs_t typedefs_; \
		simple_functions_t simple_functions_; \
		operator_functions_t operator_functions_; \
		variables_t variables_; \
 \
		namespace_ptrs_t using_directive_namespaces_; \
		using_declaration_classes_t using_declaration_classes_; \
		using_declaration_variables_t using_declaration_variables_; \
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

#undef GENERATE_NAMESPACE_DECLARATION

#include "macros/detail/declarative_region_member_impl_undef.hpp"

#endif

