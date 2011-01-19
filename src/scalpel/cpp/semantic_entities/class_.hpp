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
#include "detail/declarative_region_member_impl.hpp"
#include <scalpel/utility/shared_ptr_vector.hpp>
#include <boost/noncopyable.hpp>
#include <string>
#include <vector>
#include <map>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class namespace_;
class enum_;
class typedef_;
class constructor;
class destructor;
class operator_member_function;
class conversion_function;
class simple_member_function;
class variable;

/**
Represents a C++ class.
*/
class class_:
	public boost::noncopyable,
	public std::enable_shared_from_this<class_>
{
	public:
		typedef
			utility::variant
			<
				std::shared_ptr<const class_>,
				std::shared_ptr<const enum_>,
				std::shared_ptr<const typedef_>,
				std::shared_ptr<const constructor>,
				std::shared_ptr<const destructor>,
				std::shared_ptr<const operator_member_function>,
				std::shared_ptr<const conversion_function>,
				std::shared_ptr<const simple_member_function>,
				std::shared_ptr<const variable>
			>::type
			member_t
		;

		typedef std::vector<member_t> members_t;
		typedef std::vector<open_declarative_region_shared_ptr_variant> open_declarative_region_shared_ptr_variants_t;

		typedef utility::shared_ptr_vector<class_> classes_t;
		typedef utility::shared_ptr_vector<enum_> enums_t;
		typedef utility::shared_ptr_vector<typedef_> typedefs_t;
		typedef utility::shared_ptr_vector<constructor> constructors_t;
		typedef utility::shared_ptr_vector<operator_member_function> operator_functions_t;
		typedef utility::shared_ptr_vector<conversion_function> conversion_functions_t;
		typedef utility::shared_ptr_vector<simple_member_function> simple_functions_t;
		typedef utility::shared_ptr_vector<variable> variables_t;

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

		declarative_region_shared_ptr_variant
		enclosing_declarative_region() const;

		void
		enclosing_declarative_region(const declarative_region_shared_ptr_variant& enclosing_declarative_region);

		const open_declarative_region_shared_ptr_variants_t&
		open_declarative_regions();

		classes_t::range
		base_classes();

		const classes_t&
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

		std::shared_ptr<destructor>
		get_destructor();

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
		add_member(std::shared_ptr<enum_> member, const access acc = access::PUBLIC);

        void
        add_member(std::shared_ptr<typedef_> member, const access acc = access::PUBLIC);

        void
        add_member(std::shared_ptr<constructor> member, const access acc = access::PUBLIC);

		void
		set_destructor
		(
			std::shared_ptr<destructor> member,
			const access acc = access::PUBLIC
		);

		void
		reset_destructor();

        void
        add_member
		(
			std::shared_ptr<simple_member_function> member,
			const access acc = access::PUBLIC
		);

        void
        add_member
		(
			std::shared_ptr<operator_member_function> member,
			const access acc = access::PUBLIC
		);

        void
        add_member
		(
			std::shared_ptr<conversion_function> member,
			const access acc = access::PUBLIC
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
		is_mutable_member_variable(std::shared_ptr<const variable> member) const;

    private:
        std::string name_;
		bool complete_;
		detail::declarative_region_member_impl declarative_region_member_impl_;

		//polymorphic containers
		open_declarative_region_shared_ptr_variants_t open_declarative_regions_;

		//member information
		std::map<std::shared_ptr<const class_>, access> base_class_access_;
		classes_t virtual_base_classes_;
		std::map<const member_t, access> member_access_;
		std::vector<std::shared_ptr<const variable>> mutable_member_variables_;

		//members
		classes_t base_classes_;
		classes_t nested_classes_;
		enums_t enums_;
		typedefs_t typedefs_;
		constructors_t constructors_;
		std::shared_ptr<destructor> destructor_;
		simple_functions_t simple_functions_;
		operator_functions_t operator_functions_;
		conversion_functions_t conversion_functions_;
		variables_t variables_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif

