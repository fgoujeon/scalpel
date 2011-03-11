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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_CLASS_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_CLASS_HPP

#include "base_class.hpp"
#include "declarative_region_variants.hpp"
#include "type_variant_fwd.hpp"
#include "member_access.hpp"
#include "detail/declarative_region_member_impl.hpp"
#include <scalpel/utility/unique_ptr_vector.hpp>
#include <scalpel/utility/unique_ptr_vector.hpp>
#include <scalpel/utility/const_ptr_variant.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <string>
#include <vector>
#include <map>

#define GENERATE_CLASS_DECLARATION(CLASS_NAME, IS_MEMBER) \
class CLASS_NAME \
{ \
	public: \
		typedef std::vector<open_declarative_region_ptr_variant> open_declarative_region_ptr_variants_t; \
 \
		typedef std::vector<base_class> base_classes_t; \
		typedef utility::unique_ptr_vector<member_class> classes_t; \
		typedef utility::unique_ptr_vector<member_enum> enums_t; \
		typedef utility::unique_ptr_vector<member_typedef> typedefs_t; \
		typedef utility::unique_ptr_vector<constructor> constructors_t; \
		typedef utility::unique_ptr_vector<operator_member_function> operator_functions_t; \
		typedef utility::unique_ptr_vector<conversion_function> conversion_functions_t; \
		typedef utility::unique_ptr_vector<simple_member_function> simple_functions_t; \
		typedef utility::unique_ptr_vector<member_variable> variables_t; \
 \
	public: \
        explicit \
        CLASS_NAME \
		( \
			const std::string& name BOOST_PP_COMMA_IF(IS_MEMBER) \
			BOOST_PP_IIF(IS_MEMBER, const member_access access = member_access::PUBLIC,) \
		); \
 \
        CLASS_NAME(const CLASS_NAME&) = delete; \
 \
        const CLASS_NAME& \
		operator=(const CLASS_NAME&) = delete; \
 \
        const std::string& \
        name() const \
		{ \
			return name_; \
		} \
 \
		bool \
		complete() const \
		{ \
			return complete_; \
		} \
 \
		void \
		complete(const bool b) \
		{ \
			complete_ = b; \
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
		const open_declarative_region_ptr_variants_t& \
		open_declarative_regions(); \
 \
		const base_classes_t& \
		base_classes() const; \
 \
		classes_t::range \
		nested_classes(); \
 \
		const classes_t& \
		nested_classes() const; \
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
		constructors_t::range \
		constructors(); \
 \
		const constructors_t& \
		constructors() const; \
 \
		destructor& \
		get_destructor(); \
 \
		const destructor& \
		get_destructor() const; \
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
		conversion_functions_t::range \
		conversion_functions(); \
 \
		const conversion_functions_t& \
		conversion_functions() const; \
 \
		variables_t::range \
		variables(); \
 \
		const variables_t& \
		variables() const; \
 \
        void \
        add_base_class(const base_class& bc); \
 \
        void \
        add_member(std::unique_ptr<member_class>&& member); \
 \
		void \
		add_member(std::unique_ptr<member_enum>&& member); \
 \
        void \
        add_member(std::unique_ptr<member_typedef>&& member); \
 \
        void \
        add_member(std::unique_ptr<constructor>&& member); \
 \
		void \
		set_destructor(std::unique_ptr<destructor>&& member); \
 \
		void \
		add_member(std::unique_ptr<destructor>&& member); \
 \
		void \
		reset_destructor(); \
 \
        void \
        add_member(std::unique_ptr<simple_member_function>&& member); \
 \
        void \
        add_member(std::unique_ptr<operator_member_function>&& member); \
 \
        void \
        add_member(std::unique_ptr<conversion_function>&& member); \
 \
		void \
		add_member(std::unique_ptr<member_variable>&& member); \
 \
    private: \
        std::string name_; \
		BOOST_PP_IIF \
		( \
			IS_MEMBER, \
			member_access access_;, \
		) \
		bool complete_; \
 \
		open_declarative_region_ptr_variants_t open_declarative_regions_; \
 \
		base_classes_t base_classes_; \
		classes_t nested_classes_; \
		enums_t enums_; \
		typedefs_t typedefs_; \
		constructors_t constructors_; \
		std::unique_ptr<destructor> destructor_; \
		simple_functions_t simple_functions_; \
		operator_functions_t operator_functions_; \
		conversion_functions_t conversion_functions_; \
		variables_t variables_; \
 \
		BOOST_PP_IIF \
		( \
			IS_MEMBER, \
			DECLARATIVE_REGION_MEMBER_IMPL(member_class_declarative_region_member_impl_t), \
			DECLARATIVE_REGION_MEMBER_IMPL(detail::declarative_region_member_impl<namespace_>) \
		) \
};

namespace scalpel { namespace cpp { namespace semantic_entities
{

class member_enum;
class member_typedef;
class constructor;
class destructor;
class operator_member_function;
class conversion_function;
class simple_member_function;
class member_variable;

typedef
	detail::declarative_region_member_impl<class_, member_class>
	member_class_declarative_region_member_impl_t
;

class member_class;
GENERATE_CLASS_DECLARATION(class_, 0)
GENERATE_CLASS_DECLARATION(member_class, 1)

}}} //namespace scalpel::cpp::semantic_entities

#undef GENERATE_CLASS_DECLARATION

#endif

