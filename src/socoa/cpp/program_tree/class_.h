/*
Socoa - Source Code Analysis Library
Copyright © 2008  Florian Goujeon

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

#ifndef SOCOA_CPP_PROGRAM_TREE_CLASS_H
#define SOCOA_CPP_PROGRAM_TREE_CLASS_H

#include <string>
#include <vector>
#include <memory>
#include "namespace_member.h"
#include "class_member.h"
#include "class_enclosing_scope.h"
#include "name_tree_composite.h"

namespace socoa { namespace cpp { namespace program_tree
{

class namespace_;

/**
Represents a C++ class.
*/
class class_:
    public namespace_member,
    public class_member,
    public class_enclosing_scope,
    public virtual name_tree_composite,
    public std::enable_shared_from_this<class_>
{
    public:
        typedef class_enclosing_scope enclosing_scope;

        /**
        Creates a class.
        @param name the class' name
        */
        explicit class_(const std::string& name);

        class_(const class_& n) = delete;

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
        std::shared_ptr<name_tree_composite>
        get_enclosing_scope();

        /**
        @return the enclosing scope of the class
        */
        const std::shared_ptr<name_tree_composite>
        get_enclosing_scope() const;

        /**
        Sets the enclosing scope of the class.
        */
        void
        set_enclosing_scope(std::shared_ptr<class_> enclosing_scope);

        void
        set_enclosing_scope(std::shared_ptr<namespace_> enclosing_scope);

        /**
        @return the class' member list (i.e. the list of classes, functions, etc.)
        */
        const std::vector<std::shared_ptr<name_tree_component>>&
        get_members() const;

        const std::vector<std::shared_ptr<class_>>&
        get_classes() const;

        void
        add(std::shared_ptr<class_> member);

        void
        clear();

    private:
        /**
        Adds a member to the class.
        @param member the member to be added
        */
        void
        add_member(std::shared_ptr<class_member> member);

        std::string name_;
        std::weak_ptr<enclosing_scope> enclosing_scope_;
        std::vector<std::shared_ptr<name_tree_component>> members_;
        std::vector<std::shared_ptr<class_>> classes_;
};

}}} //namespace socoa::cpp::program_tree

#endif
