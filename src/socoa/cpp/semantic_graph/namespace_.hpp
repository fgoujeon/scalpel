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

#ifndef SOCOA_CPP_PROGRAM_TREE_NAMESPACE_HPP
#define SOCOA_CPP_PROGRAM_TREE_NAMESPACE_HPP

#include <string>
#include <vector>
#include <memory>
#include "namespace_member.hpp"
#include "namespace_enclosing_scope.hpp"
#include "class_enclosing_scope.hpp"
#include "name_tree_composite.hpp"
#include "class_.hpp"

namespace socoa { namespace cpp { namespace semantic_graph
{

/**
Represents a C++ namespace.
*/
class namespace_:
    public namespace_member,
    public namespace_enclosing_scope,
    public class_enclosing_scope,
    public virtual name_tree_composite,
    public std::enable_shared_from_this<namespace_>
{
    public:
        typedef namespace_enclosing_scope enclosing_scope;

        /**
        Creates an anonymous namespace. Equivalent to namespace_("").
        */
        namespace_();

        /**
        Creates a named namespace.
        @param name the namespace's name
        */
        explicit namespace_(const std::string& name);

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
        @return the full name of the namespace, including all enclosing scopes (e.g. ::foo::bar)
        */
        const std::string
        get_full_name() const;

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
        std::shared_ptr<name_tree_composite>
        get_enclosing_scope();

        /**
        @return the enclosing scope of the namespace
        */
        const std::shared_ptr<name_tree_composite>
        get_enclosing_scope() const;

        /**
        Sets the enclosing scope of the namespace.
        */
        void
        set_enclosing_scope(std::shared_ptr<namespace_> enclosing_scope);

        /**
        @return the namespace's member list (i.e. the list of namespaces, classes, functions, etc.)
        */
        const std::vector<std::shared_ptr<name_tree_component>>&
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

        inline
        const std::vector<base_specifier>&
        get_base_specifiers() const;

    private:
        /**
        Adds a member to the namespace.
        @param member the member to be added
        */
        void
        add_member(std::shared_ptr<namespace_member> member);

        std::string name_;
        std::weak_ptr<enclosing_scope> enclosing_scope_;
        std::vector<std::shared_ptr<name_tree_component>> members_;
        std::vector<std::shared_ptr<namespace_>> namespaces_;
        std::vector<std::shared_ptr<class_>> classes_;
        std::vector<base_specifier> empty_base_specifiers_;
};

inline
const std::vector<base_specifier>&
namespace_::get_base_specifiers() const
{
    return empty_base_specifiers_;
}

}}} //namespace socoa::cpp::semantic_graph

#endif
