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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_NAMESPACE_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_NAMESPACE_HPP

#include "variable.hpp"
#include "operator_function.hpp"
#include "simple_function.hpp"
#include "class_.hpp"
#include "named_scope.hpp"
#include "named_entity.hpp"
#include <boost/noncopyable.hpp>
#include <string>
#include <list>
#include <vector>
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents a C++ namespace.
*/
class namespace_:
	public named_scope,
	public named_entity,
	public boost::noncopyable
{
    public:
		typedef utility::shared_ptr_vector<namespace_> namespaces_t;

		typedef std::vector<std::shared_ptr<class_>> classes_t;
		typedef classes_t::const_iterator class_const_iterator;
		typedef boost::iterator_range<class_const_iterator> class_const_range;

		typedef std::vector<std::shared_ptr<simple_function>> functions_t;
		typedef functions_t::const_iterator function_const_iterator;
		typedef boost::iterator_range<function_const_iterator> function_const_range;

		typedef std::vector<std::shared_ptr<operator_function>> operator_functions_t;
		typedef operator_functions_t::const_iterator operator_function_const_iterator;
		typedef boost::iterator_range<operator_function_const_iterator> operator_function_const_range;

		typedef std::vector<std::shared_ptr<variable>> variables_t;
		typedef variables_t::const_iterator variable_const_iterator;
		typedef boost::iterator_range<variable_const_iterator> variable_const_range;

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

		named_scope_iterator_range
        named_scopes();

		named_scope_const_range
        named_scopes() const;

		named_entity_iterator_range
		named_entities();

		named_entity_const_range
		named_entities() const;

		namespaces_t::const_range
		namespaces() const;

		class_const_range
		classes() const;

		function_const_range
		functions() const;

		operator_function_const_range
		operator_functions() const;

		variable_const_range
		variables() const;

        void
        add(std::shared_ptr<namespace_> member);

        void
        add(std::shared_ptr<class_> member);

        void
        add(std::shared_ptr<simple_function> member);

        void
        add(std::shared_ptr<operator_function> member);

        void
        add(std::shared_ptr<variable> member);

    private:
        std::string name_;

		//polymorphic containers
		named_scopes_t named_scopes_;
		named_entities_t named_entities_;

		//containers
        namespaces_t namespaces_;
        classes_t classes_;
        functions_t functions_;
        operator_functions_t operator_functions_;
        variables_t variables_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif
