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
#include <vector>
#include <boost/variant.hpp>
/*#include "namespace_member.hpp"
#include "class_member.hpp"
#include "class_enclosing_scope.hpp"
#include "name_tree_composite.hpp"
#include "base_specifier.hpp"*/
#include "scope.hpp"
#include "named_item.hpp"

namespace socoa { namespace cpp { namespace semantic_graph
{

class namespace_;

/**
Represents a C++ class.
*/
class class_:
	public scope,
	public named_item
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
        @return the full name of the class, including all enclosing scopes (e.g. foo::bar)
        */
        const std::string
        get_full_name() const;

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

//        /**
//        @return true if the class has a enclosing scope scope
//        */
//        bool
//        has_enclosing_scope() const;
//
//        /**
//        @return the enclosing scope of the class
//        */
//        std::shared_ptr<name_tree_composite>
//        get_enclosing_scope();
//
//        /**
//        @return the enclosing scope of the class
//        */
//        const std::shared_ptr<name_tree_composite>
//        get_enclosing_scope() const;
//
//        /**
//        Sets the enclosing scope of the class.
//        */
//        void
//        set_enclosing_scope(std::shared_ptr<class_> enclosing_scope);
//
//        void
//        set_enclosing_scope(std::shared_ptr<namespace_> enclosing_scope);

        /**
        @return the class' member list (i.e. the list of classes, functions, etc.)
        */
        const std::vector<member_t>&
        get_members() const;

        const std::vector<scope*>&
        get_scopes() const;

        const std::vector<named_item*>&
        get_named_items() const;

//        /**
//        @return the nested classes
//        */
//        const std::vector<std::shared_ptr<class_>>&
//        get_classes() const;

        /**
        Adds a nested class.
        */
        void
        add(class_&& nested_class);

//        const std::vector<base_specifier>&
//        get_base_specifiers() const;
//
//        void
//        add(const base_specifier& specifier);

    private:
        std::string name_;
//        std::weak_ptr<enclosing_scope> enclosing_scope_;
        std::vector<member_t> members_;
        std::vector<scope*> scopes_;
        std::vector<named_item*> named_items_;
//        std::vector<std::shared_ptr<class_>> nested_classes_;
//        std::vector<base_specifier> base_specifiers_;
};

typedef
	boost::variant<class_>
	class_member_t
;

class class_::member_t: public class_member_t
{
	public:
		member_t(class_&& o): class_member_t(o){}
};

}}} //namespace socoa::cpp::semantic_graph

#endif
