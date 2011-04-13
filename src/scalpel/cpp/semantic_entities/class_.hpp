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
#include "entity_alias.hpp"
#include "declarative_region_variants.hpp"
#include "type_variant_fwd.hpp"
#include "member_access.hpp"
#include "impl/detail/declarative_region_member_impl.hpp"
#include "macros/detail/member_declaration.hpp"
#include "macros/detail/single_member_declaration.hpp"
#include "macros/detail/declarative_region_member_impl.hpp"
#include "macros/detail/hpp/member_entity_aliases_of_type.hpp"
#include <scalpel/utility/vector_range.hpp>
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
	MEMBER_DECLARATION(member_class, classes) \
	MEMBER_DECLARATION(member_enum, enums) \
	MEMBER_DECLARATION(member_typedef, typedefs) \
	MEMBER_DECLARATION(constructor, constructors) \
	SINGLE_MEMBER_DECLARATION(destructor, destructor, 0) \
	MEMBER_DECLARATION(operator_member_function, operator_functions) \
	MEMBER_DECLARATION(conversion_function, conversion_functions) \
	MEMBER_DECLARATION(simple_member_function, simple_functions) \
	MEMBER_DECLARATION(member_variable, variables) \
	MEMBER_DECLARATION(bit_field, bit_fields) \
 \
	MEMBER_ENTITY_ALIASES_OF_TYPE(member_class, class) \
	MEMBER_ENTITY_ALIASES_OF_TYPE(member_enum, enum) \
	MEMBER_ENTITY_ALIASES_OF_TYPE(member_typedef, typedef) \
	MEMBER_ENTITY_ALIASES_OF_TYPE(operator_member_function, operator_function) \
	MEMBER_ENTITY_ALIASES_OF_TYPE(conversion_function, conversion_function) \
	MEMBER_ENTITY_ALIASES_OF_TYPE(simple_member_function, simple_function) \
	MEMBER_ENTITY_ALIASES_OF_TYPE(member_variable, variable) \
	MEMBER_ENTITY_ALIASES_OF_TYPE(bit_field, bit_field) \
 \
	public: \
		typedef std::vector<base_class> base_classes_t; \
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
		const base_classes_t& \
		base_classes() const; \
 \
        void \
        add_base_class(const base_class& bc); \
 \
		void \
		reset_destructor(); \
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
		base_classes_t base_classes_; \
 \
		BOOST_PP_IIF \
		( \
			IS_MEMBER, \
			DECLARATIVE_REGION_MEMBER_IMPL(member_class_declarative_region_member_impl_t), \
			DECLARATIVE_REGION_MEMBER_IMPL(class_declarative_region_member_impl_t) \
		) \
};

namespace scalpel { namespace cpp { namespace semantic_entities
{

class namespace_;
class unnamed_namespace;
class member_enum;
class member_typedef;
class constructor;
class destructor;
class operator_member_function;
class conversion_function;
class simple_member_function;
class member_variable;
class bit_field;

typedef
	impl::detail::declarative_region_member_impl<namespace_, unnamed_namespace, linked_namespace, linked_unnamed_namespace>
	class_declarative_region_member_impl_t
;

typedef
	impl::detail::declarative_region_member_impl<class_, member_class>
	member_class_declarative_region_member_impl_t
;

class member_class;
GENERATE_CLASS_DECLARATION(class_, 0)
GENERATE_CLASS_DECLARATION(member_class, 1)

}}} //namespace scalpel::cpp::semantic_entities

#undef GENERATE_CLASS_DECLARATION

#include "macros/detail/member_declaration_undef.hpp"
#include "macros/detail/single_member_declaration_undef.hpp"
#include "macros/detail/declarative_region_member_impl_undef.hpp"
#include "macros/detail/hpp/member_entity_aliases_of_type_undef.hpp"

#endif

