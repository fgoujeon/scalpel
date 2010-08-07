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
#include <scalpel/utility/shared_ptr_vector.hpp>
#include <boost/noncopyable.hpp>
#include <string>
#include <list>
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
		class base_class;
		class constructor;
		class destructor;
		class conversion_function;

		typedef utility::shared_ptr_vector<base_class> base_classes_t;
		typedef utility::shared_ptr_vector<class_> nested_classes_t;
		typedef utility::shared_ptr_vector<constructor> constructors_t;
		typedef utility::shared_ptr_vector<simple_function> simple_functions_t;
		typedef utility::shared_ptr_vector<operator_function> operator_functions_t;
		typedef utility::shared_ptr_vector<conversion_function> conversion_functions_t;
		typedef utility::shared_ptr_vector<variable> variables_t;

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

		named_declarative_regions_t::range
        named_declarative_regions();

		named_declarative_regions_t::const_range
        named_declarative_regions() const;

		named_entities_t::range
		named_entities();

		named_entities_t::const_range
		named_entities() const;

		base_classes_t::const_range
		base_classes() const;

		nested_classes_t::const_range
		nested_classes() const;

		constructors_t::const_range
		constructors() const;

		std::shared_ptr<const destructor>
		get_destructor() const;

		void
		set_destructor(std::shared_ptr<destructor> d);

		simple_functions_t::const_range
		simple_functions() const;

		operator_functions_t::const_range
		operator_functions() const;

		conversion_functions_t::const_range
		conversion_functions() const;

		variables_t::const_range
		variables() const;

        void
        add(std::shared_ptr<base_class> c);

        /**
        Adds a nested class.
        */
        void
        add(std::shared_ptr<class_> member, access acc);

        void
        add(std::shared_ptr<constructor> member);

        void
        add
		(
			std::shared_ptr<simple_function> member,
			access acc,
			bool const_qualified,
			bool volatile_qualified,
			bool virtual_specified,
			bool pure_specified
		);

        void
        add
		(
			std::shared_ptr<operator_function> member,
			access acc,
			bool const_qualified,
			bool volatile_qualified,
			bool virtual_specified,
			bool pure_specified
		);

        void
        add(std::shared_ptr<conversion_function> member);

		void
		add(std::shared_ptr<variable> member, access acc);

    private:
        std::string name_;

		//polymorphic containers
		named_entities_t named_entities_;
		named_declarative_regions_t named_declarative_regions_;
		entities_t public_members_;
		entities_t protected_members_;
		entities_t private_members_;
		entities_t const_member_functions_;
		entities_t volatile_member_functions_;
		entities_t virtual_member_functions_;
		entities_t pure_member_functions_;

		//containers
		base_classes_t base_classes_;
		nested_classes_t nested_classes_;
		constructors_t constructors_;
		std::shared_ptr<destructor> destructor_;
		simple_functions_t simple_functions_;
		operator_functions_t operator_functions_;
		conversion_functions_t conversion_functions_;
		variables_t variables_;
};

class class_::base_class
{
	public:
		base_class
		(
			std::shared_ptr<class_> base,
			class_::access access,
			const bool is_virtual_specified
		);

		base_class(base_class&& o);

		std::shared_ptr<const class_>
		base() const;

		class_::access
		access() const;

		bool
		virtual_specified() const;

	private:
		std::shared_ptr<class_> base_;
		class_::access access_;
		bool virtual_specified_;
};

class class_::constructor
{
	public:
		typedef semantic_entities::simple_function::parameters_t parameters_t;
		typedef semantic_entities::simple_function::parameter parameter;

		constructor
		(
			parameters_t&& parameters,
			class_::access access,
			const bool is_inline_specified,
			const bool is_explicit_specified
		);

		constructor(constructor&& o);

		const parameters_t&
		parameters() const;

		class_::access
		access() const;

		bool
		inline_specified() const;

		bool
		explicit_specified() const;

	private:
		semantic_entities::simple_function impl_;
		parameters_t parameters_;
		class_::access access_;
		bool explicit_specified_;
};

class class_::destructor
{
	private:
		//give class_ access to the private constructor
		friend class class_;

		destructor
		(
			class_::access access,
			const bool is_inline_specified,
			const bool is_virtual_specified,
			const bool is_pure_specified,
			const bool is_implicitly_declared
		);

	public:
		destructor
		(
			class_::access access,
			const bool is_inline_specified,
			const bool is_virtual_specified,
			const bool is_pure_specified
		);

		destructor(destructor&& o);

		class_::access
		access() const;

		bool
		inline_specified() const;

		bool
		virtual_specified() const;

		bool
		pure_specified() const;

		bool
		implicitly_declared() const;

	private:
		class_::access access_;
		bool inline_specified_;
		bool virtual_specified_;
		bool pure_specified_;
		bool implicitly_declared_;
};

class class_::conversion_function
{
	public:
		conversion_function
		(
			std::shared_ptr<const type> t,
			class_::access access,
			const bool is_const_qualified,
			const bool is_volatile_qualified,
			const bool is_inline_specified,
			const bool is_virtual_specified,
			const bool is_pure_specified
		);

		conversion_function(conversion_function&& o);

		std::shared_ptr<const type>
		get_type() const;

		class_::access
		access() const;

		bool
		const_qualified() const;

		bool
		volatile_qualified() const;

		bool
		inline_specified() const;

		bool
		virtual_specified() const;

		bool
		pure_specified() const;

	private:
		std::shared_ptr<const type> type_;
		class_::access access_;
		bool const_qualified_;
		bool volatile_qualified_;
		bool inline_specified_;
		bool virtual_specified_;
		bool pure_specified_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif

