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

#include "declarative_region_variants.hpp"
#include "type_variant_fwd.hpp"
#include "member_access.hpp"
#include "detail/declarative_region_member_impl.hpp"
#include <scalpel/utility/unique_ptr_vector.hpp>
#include <scalpel/utility/unique_ptr_vector.hpp>
#include <scalpel/utility/const_ptr_variant.hpp>
#include <string>
#include <vector>
#include <map>

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

/**
Represents a C++ class.
*/
class class_
{
	public:
		typedef
			utility::const_ptr_variant
			<
				class_
			>::type
			member_t
		;

		typedef std::vector<member_t> members_t;
		typedef std::vector<open_declarative_region_ptr_variant> open_declarative_region_ptr_variants_t;

		typedef utility::unique_ptr_vector<class_> classes_t;
		typedef utility::unique_ptr_vector<member_enum> enums_t;
		typedef utility::unique_ptr_vector<member_typedef> typedefs_t;
		typedef utility::unique_ptr_vector<constructor> constructors_t;
		typedef utility::unique_ptr_vector<operator_member_function> operator_functions_t;
		typedef utility::unique_ptr_vector<conversion_function> conversion_functions_t;
		typedef utility::unique_ptr_vector<simple_member_function> simple_functions_t;
		typedef utility::unique_ptr_vector<member_variable> variables_t;

		typedef std::vector<class_*> class_ptrs_t;

	public:
        /**
        Creates a class.
        @param name the class' name
        */
        explicit
        class_(const std::string& name);

        class_(const class_&) = delete;

        const class_&
		operator=(const class_&) = delete;

        /**
        @return the name of the class
        */
        const std::string&
        name() const;

		bool
		complete() const
		{
			return complete_;
		}

		void
		complete(const bool b)
		{
			complete_ = b;
		}

		bool
		has_enclosing_declarative_region() const;

		declarative_region_ptr_variant
		enclosing_declarative_region() const;

		void
		enclosing_declarative_region(const declarative_region_ptr_variant& enclosing_declarative_region);

		const open_declarative_region_ptr_variants_t&
		open_declarative_regions();

		const class_ptrs_t&
		base_classes();

		const class_ptrs_t&
		base_classes() const;

		classes_t::range
		nested_classes();

		const classes_t&
		nested_classes() const;

		enums_t::range
		enums();

		const enums_t&
		enums() const;

		typedefs_t::range
		typedefs();

		const typedefs_t&
		typedefs() const;

		constructors_t::range
		constructors();

		const constructors_t&
		constructors() const;

		destructor&
		get_destructor();

		const destructor&
		get_destructor() const;

		simple_functions_t::range
		simple_functions();

		const simple_functions_t&
		simple_functions() const;

		operator_functions_t::range
		operator_functions();

		const operator_functions_t&
		operator_functions() const;

		conversion_functions_t::range
		conversion_functions();

		const conversion_functions_t&
		conversion_functions() const;

		variables_t::range
		variables();

		const variables_t&
		variables() const;

		/**
		Adds a base class.
		*/
        void
        add_base_class
		(
			class_& base_class,
			const member_access acc = member_access::PUBLIC,
			bool is_virtual = false
		);

        /**
        Adds a nested class.
        */
        void
        add_member(std::unique_ptr<class_>&& member, const member_access acc = member_access::PUBLIC);

		void
		add_member(std::unique_ptr<member_enum>&& member);

        void
        add_member(std::unique_ptr<member_typedef>&& member);

        void
        add_member(std::unique_ptr<constructor>&& member);

		void
		set_destructor(std::unique_ptr<destructor>&& member);

		void
		reset_destructor();

        void
        add_member(std::unique_ptr<simple_member_function>&& member);

        void
        add_member(std::unique_ptr<operator_member_function>&& member);

        void
        add_member(std::unique_ptr<conversion_function>&& member);

		void
		add_member(std::unique_ptr<member_variable>&& member);

		//get the member_access of the given base class
		member_access
		base_class_access(const class_& base_class) const;

		bool
		is_virtual_base_class(const class_& base_class) const;

		//get the member_access of the given class member
		member_access
		get_member_access(const member_t& member) const;

    private:
        std::string name_;
		bool complete_;
		detail::declarative_region_member_impl declarative_region_member_impl_;

		//polymorphic containers
		open_declarative_region_ptr_variants_t open_declarative_regions_;

		//member information
		std::map<const class_*, member_access> base_class_access_;
		class_ptrs_t virtual_base_classes_;
		std::map<member_t, member_access> member_access_;

		//members
		class_ptrs_t base_classes_;
		classes_t nested_classes_;
		enums_t enums_;
		typedefs_t typedefs_;
		constructors_t constructors_;
		std::unique_ptr<destructor> destructor_;
		simple_functions_t simple_functions_;
		operator_functions_t operator_functions_;
		conversion_functions_t conversion_functions_;
		variables_t variables_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif

