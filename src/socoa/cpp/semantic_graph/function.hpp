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

#ifndef SOCOA_CPP_SEMANTIC_GRAPH_FUNCTION_HPP
#define SOCOA_CPP_SEMANTIC_GRAPH_FUNCTION_HPP

#include <string>
#include <list>
#include <boost/noncopyable.hpp>
#include "scope.hpp"
#include "scope_impl.hpp"
#include "named_item.hpp"

namespace socoa { namespace cpp { namespace semantic_graph
{

class namespace_;
class class_;

/**
Represents a C++ function.
*/
class function:
	public scope,
	public named_item,
	public boost::noncopyable
{
    public:
        explicit
        function(const std::string& name);

		function(function&& f);

		const function&
		operator=(function&& f);

		void
		accept(scope_visitor& v);

        /**
        @return the name of the function
        */
        const std::string&
        get_name() const;

        /**
        @return true if the function has the given name
        */
        bool
        has_that_name(const std::string& name) const;

        /**
        @return true
        */
        bool
        is_a_type() const;

        /**
        @return false, because a function cannot be the global namespace...
        */
        bool
        is_global() const;

        /**
        @return true if the function has an enclosing scope
        */
        bool
        has_enclosing_scope() const;

        /**
        @return the enclosing scope of the function
        */
		scope&
        get_enclosing_scope();

        /**
        @return the enclosing scope of the function
        */
        const scope&
        get_enclosing_scope() const;

        /**
        Sets the enclosing scope of the function.
        */
        void
        set_enclosing_scope(class_& enclosing_scope);

        void
        set_enclosing_scope(namespace_& enclosing_scope);

		scope_iterator_range
        get_scopes();

		scope_const_iterator_range
        get_scopes() const;

		named_item_iterator_range
		get_named_items();

		named_item_const_iterator_range
		get_named_items() const;

    private:
		scope_impl scope_impl_;
        std::string name_;
};

}}} //namespace socoa::cpp::semantic_graph

#endif
