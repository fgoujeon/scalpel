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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_NAMESPACE_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_NAMESPACE_HPP

#include <string>
#include <list>
#include <boost/variant.hpp>
#include <boost/noncopyable.hpp>
#include "scope.hpp"
#include "scope_impl.hpp"
#include "named_entity.hpp"
#include "class_.hpp"
#include "function.hpp"
#include "variable.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents a C++ namespace.
*/
class namespace_:
	public scope,
	public named_entity,
	public boost::noncopyable
{
    public:
		typedef std::list<named_entity*> entities_t;
		typedef entities_t::const_iterator entity_const_iterator;
		typedef boost::indirect_iterator<entity_const_iterator, const named_entity*> entity_const_indirect_iterator;
		typedef boost::iterator_range<entity_const_indirect_iterator> entity_const_iterator_range;

		typedef std::list<namespace_> namespaces_t;
		typedef namespaces_t::const_iterator namespace_const_iterator;
		typedef boost::iterator_range<namespace_const_iterator> namespace_const_iterator_range;

		typedef std::list<class_> classes_t;
		typedef classes_t::const_iterator class_const_iterator;
		typedef boost::iterator_range<class_const_iterator> class_const_iterator_range;

		typedef std::list<function> functions_t;
		typedef functions_t::const_iterator function_const_iterator;
		typedef boost::iterator_range<function_const_iterator> function_const_iterator_range;

		typedef std::list<variable> variables_t;
		typedef variables_t::const_iterator variable_const_iterator;
		typedef boost::iterator_range<variable_const_iterator> variable_const_iterator_range;

        /**
        Creates an anonymous namespace. Equivalent to namespace_("").
        */
        namespace_();

        /**
        Creates a named namespace.
        @param name the namespace's name
        */
        explicit
		namespace_(const std::string& name);

		/**
		 * Move constructor.
		 */
		namespace_(namespace_&& n);

		/**
		 * Move assignment operator.
		 */
		const namespace_&
		operator=(namespace_&& n);

		void
		accept(scope_visitor& v);

        /**
        @return the name of the namespace
        Anonymous namespaces return an empty string.
        */
        const std::string&
        name() const;

        bool
        is_a_type() const;

        /**
        @return true if the namespace is the global one, false otherwise
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

		namespace_const_iterator_range
		namespaces() const;

		class_const_iterator_range
		classes() const;

		function_const_iterator_range
		functions() const;

		variable_const_iterator_range
		variables() const;

        void
        add(namespace_&& member);

        void
        add(class_&& member);

        void
        add(function&& member);

        void
        add(variable&& member);

    private:
		scope_impl scope_impl_;
        std::string name_;
        namespaces_t namespaces_;
        classes_t classes_;
        functions_t functions_;
        variables_t variables_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif
