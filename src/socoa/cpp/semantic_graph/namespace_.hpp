/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_SEMANTIC_GRAPH_NAMESPACE_HPP
#define SOCOA_CPP_SEMANTIC_GRAPH_NAMESPACE_HPP

#include <string>
#include <list>
#include <boost/variant.hpp>
#include <boost/noncopyable.hpp>
#include "scope.hpp"
#include "scope_impl.hpp"
#include "named_item.hpp"
#include "class_.hpp"
#include "function.hpp"
#include "variable.hpp"

namespace socoa { namespace cpp { namespace semantic_graph
{

/**
Represents a C++ namespace.
*/
class namespace_:
	public scope,
	public named_item,
	public boost::noncopyable
{
    public:
		class member_t;

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
        get_name() const;

        /**
        @return true if the namespace has the given name
        */
        bool
        has_that_name(const std::string& name) const;

        bool
        is_a_type() const;

        /**
        @return true if the namespace is the global one, false otherwise
        */
        bool
        is_global() const;

        /**
        @return true if the namespace has a enclosing scope scope
        */
        bool
        has_enclosing_scope() const;

        /**
        @return the enclosing scope of the namespace
        */
		scope&
        get_enclosing_scope();

        /**
        @return the enclosing scope of the namespace
        */
		const scope&
        get_enclosing_scope() const;

        /**
        Sets the enclosing scope of the namespace.
        */
        void
        set_enclosing_scope(namespace_& enclosing_scope);

        /**
        @return the namespace's member list (i.e. the list of namespaces, classes, functions, etc.)
        */
        const std::list<member_t>&
        get_members() const;

		scope_iterator_range
        get_scopes();

		scope_const_iterator_range
        get_scopes() const;

		named_item_iterator_range
		get_named_items();

		named_item_const_iterator_range
		get_named_items() const;

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
        std::list<namespace_> namespaces_;
        std::list<class_> classes_;
        std::list<function> functions_;
        std::list<variable> variables_;
        std::list<member_t> members_;
};

typedef
	boost::variant
	<
		namespace_*,
		class_*,
		function*,
		variable*
	>
	namespace_member_t
;

class namespace_::member_t: public namespace_member_t
{
	public:
		member_t(namespace_* o): namespace_member_t(o){}
		member_t(class_* o): namespace_member_t(o){}
		member_t(function* o): namespace_member_t(o){}
		member_t(variable* o): namespace_member_t(o){}
};

}}} //namespace socoa::cpp::semantic_graph

#endif
