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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_CLASS_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_CLASS_HPP

#include "typedef_.hpp"
#include "variable.hpp"
#include "operator_function.hpp"
#include "simple_function.hpp"
#include "declarative_region_member_impl.hpp"
#include "declarative_region_variants.hpp"
#include "type_variants_fwd.hpp"
#include <scalpel/utility/vector.hpp>
#include <boost/noncopyable.hpp>
#include <string>
#include <vector>
#include <map>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class namespace_;

/**
Represents a C++ class.
*/
class class_:
	public boost::noncopyable,
	public std::enable_shared_from_this<class_>
{
	public:
		class constructor;
		class destructor;
		class conversion_function;

		typedef
			utility::variant
			<
				std::shared_ptr<const class_>,
				std::shared_ptr<const typedef_>,
				std::shared_ptr<const constructor>,
				std::shared_ptr<const destructor>,
				std::shared_ptr<const simple_function>,
				std::shared_ptr<const conversion_function>,
				std::shared_ptr<const operator_function>,
				std::shared_ptr<const variable>
			>
			member_t
		;

		typedef utility::vector<member_t> members_t;
		typedef utility::vector<open_declarative_region_shared_ptr_variant> open_declarative_region_shared_ptr_variants_t;
		typedef utility::vector<named_compound_type_shared_ptr_variant> named_compound_type_shared_ptr_variants_t;

		typedef utility::vector<std::shared_ptr<class_>> classes_t;
		typedef utility::vector<std::shared_ptr<typedef_>> typedefs_t;
		typedef utility::vector<std::shared_ptr<constructor>> constructors_t;
		typedef utility::vector<std::shared_ptr<simple_function>> simple_functions_t;
		typedef utility::vector<std::shared_ptr<operator_function>> operator_functions_t;
		typedef utility::vector<std::shared_ptr<conversion_function>> conversion_functions_t;
		typedef utility::vector<std::shared_ptr<variable>> variables_t;

		enum class access
		{
			PUBLIC,
			PROTECTED,
			PRIVATE
		};

	private:
        /**
        Creates a class.
        @param name the class' name
        */
        explicit
        class_(const std::string& name);

	public:
        /**
        Creates a class.
        @param name the class' name
        */
		static
		std::shared_ptr<class_>
		make_shared(const std::string& name);

        /**
        @return the name of the class
        */
        const std::string&
        name() const;

		bool
		has_enclosing_declarative_region() const;

		declarative_region_shared_ptr_variant
		enclosing_declarative_region() const;

		void
		enclosing_declarative_region(const declarative_region_shared_ptr_variant& enclosing_declarative_region);

		const open_declarative_region_shared_ptr_variants_t&
		open_declarative_regions();

		const named_compound_type_shared_ptr_variants_t&
		named_compound_types();

		classes_t::range
		base_classes();

		const classes_t&
		base_classes() const;

		classes_t::range
		nested_classes();

		const classes_t&
		nested_classes() const;

		const typedefs_t&
		typedefs() const;

		constructors_t::range
		constructors();

		const constructors_t&
		constructors() const;

		std::shared_ptr<const destructor>
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
			std::shared_ptr<class_> base_class,
			const access acc = access::PUBLIC,
			bool is_virtual = false
		);

        /**
        Adds a nested class.
        */
        void
        add_member(std::shared_ptr<class_> member, const access acc = access::PUBLIC);

        void
        add_member(std::shared_ptr<typedef_> member, const access acc = access::PUBLIC);

        void
        add_member(std::shared_ptr<constructor> member, const access acc = access::PUBLIC);

		void
		set_destructor
		(
			std::shared_ptr<destructor> member,
			const access acc = access::PUBLIC,
			const bool is_virtual = false,
			const bool is_pure = false
		);

		void
		reset_destructor();

        void
        add_member
		(
			std::shared_ptr<simple_function> member,
			const access acc = access::PUBLIC,
			const bool is_const = false,
			const bool is_volatile = false,
			const bool is_virtual = false,
			const bool is_pure = false
		);

        void
        add_member
		(
			std::shared_ptr<operator_function> member,
			const access acc = access::PUBLIC,
			const bool is_const = false,
			const bool is_volatile = false,
			const bool is_virtual = false,
			const bool is_pure = false
		);

        void
        add_member
		(
			std::shared_ptr<conversion_function> member,
			const access acc = access::PUBLIC,
			const bool is_const = false,
			const bool is_volatile = false,
			const bool is_virtual = false,
			const bool is_pure = false
		);

		void
		add_member
		(
			std::shared_ptr<variable> member,
			const access acc = access::PUBLIC,
			const bool is_mutable = false
		);

		//get the access of the given base class
		access
		base_class_access(std::shared_ptr<const class_> base_class) const;

		bool
		is_virtual_base_class(std::shared_ptr<const class_> base_class) const;

		//get the access of the given class member
		access
		member_access(const member_t& member) const;

		bool
		is_const_member_function(const member_t& member) const;

		bool
		is_volatile_member_function(const member_t& member) const;

		bool
		is_virtual_member_function(const member_t& member) const;

		bool
		is_pure_member_function(const member_t& member) const;

		bool
		is_mutable_member_variable(std::shared_ptr<const variable> member) const;

    private:
        std::string name_;
		declarative_region_member_impl declarative_region_member_impl_;

		//polymorphic containers
		open_declarative_region_shared_ptr_variants_t open_declarative_regions_;
		named_compound_type_shared_ptr_variants_t named_compound_types_;

		//member information
		std::map<std::shared_ptr<const class_>, access> base_class_access_;
		classes_t virtual_base_classes_;
		std::map<const member_t, access> member_access_;
		members_t const_member_functions_;
		members_t volatile_member_functions_;
		members_t virtual_member_functions_;
		members_t pure_member_functions_;
		std::vector<std::shared_ptr<const variable>> mutable_member_variables_;

		//members
		classes_t base_classes_;
		classes_t nested_classes_;
		typedefs_t typedefs_;
		constructors_t constructors_;
		std::shared_ptr<destructor> destructor_;
		simple_functions_t simple_functions_;
		operator_functions_t operator_functions_;
		conversion_functions_t conversion_functions_;
		variables_t variables_;
};

bool
operator==(const class_& lhs, const class_& rhs);

bool
operator!=(const class_& lhs, const class_& rhs);



class class_::constructor
{
	public:
		typedef simple_function::parameter parameter;
		typedef simple_function::parameters_t parameters_t;

		constructor
		(
			parameters_t&& parameters,
			const bool is_inline,
			const bool is_explicit
		);

		constructor(constructor&& o);

		bool
		operator==(const constructor& rhs) const;

		bool
		operator!=(const constructor& rhs) const;

		const parameters_t&
		parameters() const;

		bool
		is_inline() const;

		bool
		is_explicit() const;

		bool
		has_enclosing_declarative_region() const;

		declarative_region_shared_ptr_variant
		enclosing_declarative_region() const;

		void
		enclosing_declarative_region(const declarative_region_shared_ptr_variant& enclosing_declarative_region);

	private:
		std::shared_ptr<semantic_entities::simple_function> impl_;
		bool is_explicit_;
		declarative_region_member_impl declarative_region_member_impl_;
};



class class_::destructor
{
	public:
		destructor(const bool is_inline);

		destructor(destructor&& o);

		bool
		is_inline() const;

		bool
		has_enclosing_declarative_region() const;

		declarative_region_shared_ptr_variant
		enclosing_declarative_region() const;

		void
		enclosing_declarative_region(const declarative_region_shared_ptr_variant& enclosing_declarative_region);

	private:
		bool is_inline_;
		declarative_region_member_impl declarative_region_member_impl_;
};

bool
operator==(const class_::destructor& lhs, const class_::destructor& rhs);

bool
operator!=(const class_::destructor& lhs, const class_::destructor& rhs);



class class_::conversion_function
{
	public:
		conversion_function
		(
			const type_shared_ptr_variant& return_type,
			const bool is_inline
		);

		conversion_function(conversion_function&& o);

		const type_shared_ptr_variant&
		return_type() const;

		bool
		is_inline() const;

		bool
		has_enclosing_declarative_region() const;

		declarative_region_shared_ptr_variant
		enclosing_declarative_region() const;

		void
		enclosing_declarative_region(const declarative_region_shared_ptr_variant& enclosing_declarative_region);

	private:
		type_shared_ptr_variant return_type_;
		bool is_inline_;
		declarative_region_member_impl declarative_region_member_impl_;
};

bool
operator==(const class_::conversion_function& lhs, const class_::conversion_function& rhs);

bool
operator!=(const class_::conversion_function& lhs, const class_::conversion_function& rhs);

}}} //namespace scalpel::cpp::semantic_entities

#endif

