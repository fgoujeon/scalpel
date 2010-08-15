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

#include "variable.hpp"
#include "operator_function.hpp"
#include "simple_function.hpp"
#include "named_declarative_region.hpp"
#include "named_entity.hpp"
#include "type.hpp"
#include <scalpel/utility/vector.hpp>
#include <boost/noncopyable.hpp>
#include <string>
#include <vector>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class namespace_;

/**
Represents a C++ class.
*/
class class_:
	public named_declarative_region,
	public type,
	public boost::noncopyable
{
	public:
		class constructor;
		class destructor;
		class conversion_function;

		typedef utility::vector<std::shared_ptr<class_>> classes_t;
		typedef utility::vector<std::shared_ptr<constructor>> constructors_t;
		typedef utility::vector<std::shared_ptr<simple_function>> simple_functions_t;
		typedef utility::vector<std::shared_ptr<operator_function>> operator_functions_t;
		typedef utility::vector<std::shared_ptr<conversion_function>> conversion_functions_t;
		typedef utility::vector<std::shared_ptr<variable>> variables_t;

		enum access
		{
			PUBLIC,
			PROTECTED,
			PRIVATE
		};

        /**
        Creates a class.
        @param name the class' name
        */
        explicit
        class_(const std::string& name);

		/**
		 * Move constructor.
		 */
		class_(class_&& c);

		/**
		 * Move assignment operator.
		 */
		const class_&
		operator=(class_&& c);

        /**
        @return the name of the class
        */
        const std::string&
        name() const;

        /**
        @return false, because a class cannot be the global namespace...
        */
        bool
        is_global() const;

        /**
        @return true
        */
		bool
		is_open_to_outside() const;

		named_entities_t::range
		named_entities();

		const named_entities_t&
		named_entities() const;

		named_declarative_regions_t::range
        named_declarative_regions();

		const named_declarative_regions_t&
        named_declarative_regions() const;

		classes_t::range
		base_classes();

		const classes_t&
		base_classes() const;

		classes_t::range
		nested_classes();

		const classes_t&
		nested_classes() const;

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
			const access acc = PUBLIC,
			bool virtual_specified = false
		);

        /**
        Adds a nested class.
        */
        void
        add(std::shared_ptr<class_> member, const access acc = PUBLIC);

        void
        add(std::shared_ptr<constructor> member, const access acc = PUBLIC);

		void
		set_destructor
		(
			std::shared_ptr<destructor> member,
			const access acc = PUBLIC,
			const bool virtual_specified = false,
			const bool pure_specified = false
		);

        void
        add
		(
			std::shared_ptr<simple_function> member,
			const access acc = PUBLIC,
			const bool const_qualified = false,
			const bool volatile_qualified = false,
			const bool virtual_specified = false,
			const bool pure_specified = false
		);

        void
        add
		(
			std::shared_ptr<operator_function> member,
			const access acc = PUBLIC,
			const bool const_qualified = false,
			const bool volatile_qualified = false,
			const bool virtual_specified = false,
			const bool pure_specified = false
		);

        void
        add
		(
			std::shared_ptr<conversion_function> member,
			const access acc = PUBLIC,
			const bool const_qualified = false,
			const bool volatile_qualified = false,
			const bool virtual_specified = false,
			const bool pure_specified = false
		);

		void
		add(std::shared_ptr<variable> member, const access acc);

    private:
        std::string name_;

		//polymorphic containers
		named_entities_t named_entities_;
		named_declarative_regions_t named_declarative_regions_;
		classes_t public_base_classes_;
		classes_t protected_base_classes_;
		classes_t private_base_classes_;
		classes_t virtual_base_classes_;
		entities_t public_members_;
		entities_t protected_members_;
		entities_t private_members_;
		entities_t const_member_functions_;
		entities_t volatile_member_functions_;
		entities_t virtual_member_functions_;
		entities_t pure_member_functions_;

		//containers
		classes_t base_classes_;
		classes_t nested_classes_;
		constructors_t constructors_;
		std::shared_ptr<destructor> destructor_;
		simple_functions_t simple_functions_;
		operator_functions_t operator_functions_;
		conversion_functions_t conversion_functions_;
		variables_t variables_;
};

class class_::constructor: public entity
{
	public:
		typedef simple_function::parameter parameter;
		typedef simple_function::parameters_t parameters_t;

		constructor
		(
			parameters_t&& parameters,
			const bool is_inline_specified,
			const bool is_explicit_specified
		);

		constructor(constructor&& o);

		const parameters_t&
		parameters() const;

		bool
		inline_specified() const;

		bool
		explicit_specified() const;

	private:
		semantic_entities::simple_function impl_;
		bool explicit_specified_;
};

class class_::destructor: public entity
{
	public:
		destructor(const bool is_inline_specified);

		destructor(destructor&& o);

		bool
		inline_specified() const;

	private:
		bool inline_specified_;
};

class class_::conversion_function: public entity
{
	public:
		conversion_function
		(
			std::shared_ptr<const type> return_type,
			const bool is_inline_specified
		);

		conversion_function(conversion_function&& o);

		std::shared_ptr<const type>
		return_type() const;

		bool
		inline_specified() const;

	private:
		std::shared_ptr<const type> return_type_;
		bool inline_specified_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif

