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
#include "class_parent.h"
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
    public class_parent,
    public virtual name_tree_composite,
    public std::enable_shared_from_this<class_>
{
    public:
        typedef class_parent parent;

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
        @return the full name of the class, including all parent scopes (e.g. foo::bar)
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
        @return true if the class has a parent scope
        */
        bool
        has_parent() const;

        /**
        @return the parent of the class
        */
        std::shared_ptr<name_tree_composite>
        get_parent();

        /**
        @return the parent of the class
        */
        const std::shared_ptr<name_tree_composite>
        get_parent() const;

        /**
        Sets the parent of the class.
        */
        void
        set_parent(std::shared_ptr<class_> parent);

        void
        set_parent(std::shared_ptr<namespace_> parent);

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
        std::weak_ptr<parent> parent_;
        std::vector<std::shared_ptr<name_tree_component>> members_;
        std::vector<std::shared_ptr<class_>> classes_;
};

}}} //namespace socoa::cpp::program_tree

#endif
