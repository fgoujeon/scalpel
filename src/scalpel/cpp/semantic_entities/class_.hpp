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
		template<class EntityT>
		class member;

		template<class EntityT>
		class function_member;

		class base_class;
		typedef member<class_> nested_class;
		class constructor;
		class destructor;
		class conversion_function;
		class simple_function;
		typedef function_member<semantic_entities::operator_function> operator_function;
		typedef member<semantic_entities::variable> variable;

		typedef utility::shared_ptr_vector<base_class> base_classes_t;
		typedef utility::shared_ptr_vector<nested_class> nested_classes_t;
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
        add(std::shared_ptr<nested_class> member);

        void
        add(std::shared_ptr<constructor> member);

        void
        add(std::shared_ptr<simple_function> member);

        void
        add(std::shared_ptr<operator_function> member);

        void
        add(std::shared_ptr<conversion_function> member);

		void
		add(std::shared_ptr<variable> member);

    private:
        std::string name_;

		//polymorphic containers
		named_entities_t named_entities_;
		named_declarative_regions_t named_declarative_regions_;

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

template<class EntityT>
class class_::member
{
	public:
		member(std::shared_ptr<EntityT> entity, class_::access a);

		member(const member& o);

		member(member&& o);

		std::shared_ptr<const EntityT>
		entity() const;

		std::shared_ptr<EntityT>
		entity();

		class_::access
		access() const;

	private:
		std::shared_ptr<EntityT> entity_;
		class_::access access_;
};

template<class EntityT>
class class_::function_member
{
	public:
		function_member
		(
			std::shared_ptr<EntityT> entity,
			class_::access a,
			bool is_const_qualified,
			bool is_volatile_qualified,
			bool is_inline_specified,
			bool is_virtual_specified,
			bool is_pure_specified
		);

		function_member(function_member&& o);

		std::shared_ptr<const EntityT>
		entity() const;

		std::shared_ptr<EntityT>
		entity();

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
		std::shared_ptr<EntityT> entity_;
		class_::access access_;
		bool const_qualified_;
		bool volatile_qualified_;
		bool inline_specified_;
		bool virtual_specified_;
		bool pure_specified_;
};

class class_::simple_function: public named_declarative_region, public class_::function_member<semantic_entities::simple_function>
{
	public:
		simple_function
		(
			std::shared_ptr<semantic_entities::simple_function> raw_simple_function,
			class_::access a,
			bool is_const_qualified,
			bool is_volatile_qualified,
			bool is_inline_specified,
			bool is_virtual_specified,
			bool is_pure_specified
		);

		simple_function(simple_function&& o);

		const std::string&
		name() const
		{
			return entity()->name();
		}

		named_declarative_regions_t::range
		named_declarative_regions()
		{
			return entity()->named_declarative_regions();
		}

		named_declarative_regions_t::const_range
		named_declarative_regions() const
		{
			return entity()->named_declarative_regions();
		}

		named_entities_t::range
		named_entities()
		{
			return entity()->named_entities();
		}

		named_entities_t::const_range
		named_entities() const
		{
			return entity()->named_entities();
		}

		bool
		is_open_to_outside() const
		{
			return entity()->is_open_to_outside();
		}
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

template<>
class class_::member<class_>:
	public named_declarative_region,
	public type
{
	public:
		member(std::shared_ptr<class_> c, class_::access a);

		member(const member& o);

		member(member&& o);

        const std::string&
        name() const
		{
			return entity_->name();
		}

        bool
        is_open_to_outside() const
		{
			return true;
		}

		class_::named_declarative_regions_t::range
        named_declarative_regions()
		{
			return entity_->named_declarative_regions();
		}

		class_::named_declarative_regions_t::const_range
        named_declarative_regions() const
		{
			return entity_->named_declarative_regions();
		}

		class_::named_entities_t::range
		named_entities()
		{
			return entity_->named_entities();
		}

		class_::named_entities_t::const_range
		named_entities() const
		{
			return entity_->named_entities();
		}

		std::shared_ptr<const class_>
		entity() const
		{
			return entity_;
		}

		std::shared_ptr<class_>
		entity()
		{
			return entity_;
		}

		class_::access
		access() const;

	private:
		std::shared_ptr<class_> entity_;
		class_::access access_;
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
		bool inline_specified_;
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



template<class EntityT>
class_::member<EntityT>::member(std::shared_ptr<EntityT> entity, class_::access a):
	entity_(std::move(entity)),
	access_(a)
{
}

template<class EntityT>
class_::member<EntityT>::member(const member<EntityT>& o):
	entity_(o.entity_),
	access_(o.access_)
{
}

template<class EntityT>
class_::member<EntityT>::member(member<EntityT>&& o):
	entity_(std::move(o.entity_)),
	access_(o.access_)
{
}

template<class EntityT>
std::shared_ptr<const EntityT>
class_::member<EntityT>::entity() const
{
	return entity_;
}

template<class EntityT>
std::shared_ptr<EntityT>
class_::member<EntityT>::entity()
{
	return entity_;
}

template<class EntityT>
class_::access
class_::member<EntityT>::access() const
{
	return access_;
}



template<class EntityT>
class_::function_member<EntityT>::function_member
(
	std::shared_ptr<EntityT> entity,
	class_::access a,
	bool is_const_qualified,
	bool is_volatile_qualified,
	bool is_inline_specified,
	bool is_virtual_specified,
	bool is_pure_specified
):
	entity_(entity),
	access_(a),
	const_qualified_(is_const_qualified),
	volatile_qualified_(is_volatile_qualified),
	inline_specified_(is_inline_specified),
	virtual_specified_(is_virtual_specified),
	pure_specified_(is_pure_specified)
{
}

template<class EntityT>
class_::function_member<EntityT>::function_member(function_member&& o):
	entity_(o.entity_),
	access_(o.access_),
	const_qualified_(o.const_qualified_),
	volatile_qualified_(o.volatile_qualified_),
	inline_specified_(o.inline_specified_),
	virtual_specified_(o.virtual_specified_),
	pure_specified_(o.pure_specified_)
{
}

template<class EntityT>
std::shared_ptr<const EntityT>
class_::function_member<EntityT>::entity() const
{
	return entity_;
}

template<class EntityT>
std::shared_ptr<EntityT>
class_::function_member<EntityT>::entity()
{
	return entity_;
}

template<class EntityT>
class_::access
class_::function_member<EntityT>::access() const
{
	return access_;
}

template<class EntityT>
bool
class_::function_member<EntityT>::const_qualified() const
{
	return const_qualified_;
}

template<class EntityT>
bool
class_::function_member<EntityT>::volatile_qualified() const
{
	return volatile_qualified_;
}

template<class EntityT>
bool
class_::function_member<EntityT>::inline_specified() const
{
	return inline_specified_;
}

template<class EntityT>
bool
class_::function_member<EntityT>::virtual_specified() const
{
	return virtual_specified_;
}

template<class EntityT>
bool
class_::function_member<EntityT>::pure_specified() const
{
	return pure_specified_;
}

}}} //namespace scalpel::cpp::semantic_entities

#endif
