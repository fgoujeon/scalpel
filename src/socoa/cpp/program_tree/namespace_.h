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

#ifndef SOCOA_CPP_PROGRAM_TREE_NAMESPACE_H
#define SOCOA_CPP_PROGRAM_TREE_NAMESPACE_H

#include <string>
#include <vector>
#include <memory>
#include "namespace_member.h"
#include "namespace_member_impl.h"
#include "namespace_parent.h"
#include "class_parent.h"
#include "named_scope.h"
#include "class_.h"

namespace socoa { namespace cpp { namespace program_tree
{

/**
Represents a C++ namespace.
*/
class namespace_:
    public namespace_member,
    public namespace_parent,
    public class_parent,
    public virtual named_scope,
    public std::enable_shared_from_this<namespace_>
{
    public:
        typedef namespace_parent parent;

        /**
        Creates an anonymous namespace. Equivalent to namespace_("").
        */
        namespace_();

        /**
        Creates a named namespace.
        @param name the namespace's name
        */
        explicit namespace_(const std::string& name);

        namespace_(const namespace_& n) = delete;

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

        /**
        @return the full name of the namespace, including all parent namespaces (e.g. ::foo::bar)
        */
        const std::string
        get_full_name() const;

        /**
        @return true if the namespace is the global one, false otherwise
        */
        bool
        is_global() const;

        /**
        @return true if the namespace has a parent scope
        */
        bool
        has_parent() const
        {
            return namespace_member_impl_.has_parent();
        }

        /**
        @return the parent of the namespace
        */
        std::shared_ptr<named_scope>
        get_parent()
        {
            return namespace_member_impl_.get_parent();
        }

        /**
        @return the parent of the namespace
        */
        const std::shared_ptr<named_scope>
        get_parent() const
        {
            return namespace_member_impl_.get_parent();
        }

        /**
        Sets the parent of the namespace.
        */
        void
        set_parent(std::shared_ptr<namespace_> parent)
        {
            namespace_member_impl_.set_parent(parent);
        }

        /**
        @return the namespace's member list (i.e. the list of namespaces, classes, functions, etc.)
        */
        const std::vector<std::shared_ptr<namespace_member>>&
        get_members() const;

        template <class ScopeT>
        const std::vector<std::shared_ptr<ScopeT>>&
        get_members() const;

        /**
        @return the namespace's namespace member list (i.e. the list of namespaces without classes, functions, etc.)
        */
        const std::vector<std::shared_ptr<namespace_>>&
        get_namespaces() const;

        const std::vector<std::shared_ptr<class_>>&
        get_classes() const;

        void
        add(std::shared_ptr<namespace_> member);

        void
        add(std::shared_ptr<class_> member);

        void
        clear();

    private:
        /**
        Adds a member to the namespace.
        @param member the member to be added
        */
        void
        add_member(std::shared_ptr<namespace_member> member);

        namespace_member_impl namespace_member_impl_;
        std::string name_;
        std::vector<std::shared_ptr<namespace_member>> members_;
        std::vector<std::shared_ptr<namespace_>> namespaces_;
        std::vector<std::shared_ptr<class_>> classes_;
};

}}} //namespace socoa::cpp::program_tree

#endif
