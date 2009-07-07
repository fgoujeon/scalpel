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

        /**
        @return the class' member list (i.e. the list of classes, functions, etc.)
        */
        const std::list<member_t>&
        members() const;

		scope_iterator_range
        scopes();

		scope_const_iterator_range
        scopes() const;

		named_entity_iterator_range
		named_entities();

		named_entity_const_iterator_range
		named_entities() const;

        /**
        Adds a nested class.
        */
        void
        add(class_&& nested_class);

        void
        add(function&& member);

		void
		add(variable&& member);

    private:
		scope_impl scope_impl_;
        std::string name_;
		std::list<class_> classes_;
		std::list<function> functions_;
		std::list<variable> variables_;
        std::list<member_t> members_;
};

typedef
	boost::variant
	<
		class_*,
		function*,
		variable*
	>
	class_member_t
;

class class_::member_t: public class_member_t
{
	public:
		member_t(class_* o): class_member_t(o){}
		member_t(function* o): class_member_t(o){}
		member_t(variable* o): class_member_t(o){}
};

}}} //namespace scalpel::cpp::semantic_entities

#endif
