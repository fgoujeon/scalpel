/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_CLASS_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_CLASS_HPP

#include <string>
#include <list>
#include <boost/variant.hpp>
#include <boost/noncopyable.hpp>
#include "type.hpp"
#include "scope.hpp"
#include "scope_impl.hpp"
#include "named_entity.hpp"
#include "function.hpp"
#include "variable.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

class namespace_;

/**
Represents a C++ class.
*/
class class_:
	public scope,
	public named_entity,
	public type,
	public boost::noncopyable
{
    public:
		class constructor;

		template<class EntityT>
		class member;

		typedef std::list<member<class_>> classes_t;
		typedef classes_t::const_iterator class_const_iterator;
		typedef boost::iterator_range<class_const_iterator> class_const_iterator_range;

		typedef std::list<constructor> constructors_t;
		typedef constructors_t::const_iterator constructor_const_iterator;
		typedef boost::iterator_range<constructor_const_iterator> constructor_const_iterator_range;

		typedef std::list<member<function>> functions_t;
		typedef functions_t::const_iterator function_const_iterator;
		typedef boost::iterator_range<function_const_iterator> function_const_iterator_range;

		typedef std::list<member<variable>> variables_t;
		typedef variables_t::const_iterator variable_const_iterator;
		typedef boost::iterator_range<variable_const_iterator> variable_const_iterator_range;

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

		/*
		 * Move assignment operator.
		 */
		const class_&
		operator=(class_&& c);

		void
		accept(scope_visitor& v);

        /**
        @return the name of the class
        */
        const std::string&
        name() const;

        /**
        @return true
        */
        bool
        is_a_type() const;

        /**
        @return false, because a class cannot be the global namespace...
        */
        bool
        is_global() const;

		scope_iterator_range
        scopes();

		scope_const_iterator_range
        scopes() const;

		named_entity_iterator_range
		named_entities();

		named_entity_const_iterator_range
		named_entities() const;

		class_const_iterator_range
		classes() const;

		constructor_const_iterator_range
		constructors() const;

		function_const_iterator_range
		functions() const;

		variable_const_iterator_range
		variables() const;

        /**
        Adds a nested class.
        */
        void
        add(member<class_>&& nested_class);

        void
        add(constructor&& member);

        void
        add(member<function>&& member);

		void
		add(member<variable>&& member);

    private:
		scope_impl scope_impl_;
        std::string name_;
		classes_t classes_;
		constructors_t constructors_;
		functions_t functions_;
		variables_t variables_;
};

class class_::constructor
{
	public:
		typedef function::parameters_t parameters_t;
		typedef function::parameter parameter;

		constructor(parameters_t&& parameters, class_::access access);

		constructor(constructor&& o);

		const parameters_t&
		parameters() const;

		class_::access
		access() const;

	private:
		function impl_;
		parameters_t parameters_;
		class_::access access_;
};

template<class EntityT>
class class_::member
{
	public:
		member(EntityT&& entity, class_::access a);

		member(const member& o);

		member(member&& o);

		const EntityT&
		entity() const;

		EntityT&
		entity();

		class_::access
		access() const;

	private:
		EntityT entity_;
		class_::access access_;
};

template<class EntityT>
class_::member<EntityT>::member(EntityT&& entity, class_::access a):
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
const EntityT&
class_::member<EntityT>::entity() const
{
	return entity_;
}

template<class EntityT>
EntityT&
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

}}} //namespace scalpel::cpp::semantic_entities

#endif
