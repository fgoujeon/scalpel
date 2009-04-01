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

#ifndef SOCOA_CPP_SEMANTIC_GRAPH_CLASS_HPP
#define SOCOA_CPP_SEMANTIC_GRAPH_CLASS_HPP

#include <string>
#include <list>
#include <boost/variant.hpp>
#include <boost/noncopyable.hpp>
#include "scope.hpp"
#include "scope_impl.hpp"
#include "named_item.hpp"
#include "function.hpp"

namespace socoa { namespace cpp { namespace semantic_graph
{

class namespace_;

/**
Represents a C++ class.
*/
class class_:
	public scope,
	public named_item,
	public boost::noncopyable
{
    public:
		class member_t;

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
        get_name() const;

        /**
        @return true if the class has the given name
        */
        bool
        has_that_name(const std::string& name) const;

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

        /**
        @return true if the class has a enclosing scope scope
        */
        bool
        has_enclosing_scope() const;

        /**
        @return the enclosing scope of the class
        */
		scope&
        get_enclosing_scope();

        /**
        @return the enclosing scope of the class
        */
        const scope&
        get_enclosing_scope() const;

        /**
        Sets the enclosing scope of the class.
        */
        void
        set_enclosing_scope(class_& enclosing_scope);

        void
        set_enclosing_scope(namespace_& enclosing_scope);

        /**
        @return the class' member list (i.e. the list of classes, functions, etc.)
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

        /**
        Adds a nested class.
        */
        void
        add(class_&& nested_class);

        void
        add(function&& member);

    private:
		scope_impl scope_impl_;
        std::string name_;
		std::list<class_> classes_;
		std::list<function> functions_;
        std::list<member_t> members_;
};

typedef
	boost::variant
	<
		class_*,
		function*
	>
	class_member_t
;

class class_::member_t: public class_member_t
{
	public:
		member_t(class_* o): class_member_t(o){}
		member_t(function* o): class_member_t(o){}
};

}}} //namespace socoa::cpp::semantic_graph

#endif
