/*
Socoa - Source Code Analysis Library
Copyright © 2008  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

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
#include <stdexcept>
#include "namespace_member.h"
#include "class_.h"
#include "union_.h"

namespace socoa { namespace cpp { namespace program_tree
{

class class_;
class enum_;
class typedef_;

/**
Represents a C++ namespace.
*/
class namespace_: public namespace_member, public std::enable_shared_from_this<namespace_>
{
    public:
        /**
        Creates an anonymous namespace. Equivalent to namespace_("").
        */
        namespace_();

        /**
        Creates a named namespace.
        @param name the namespace's name
        */
        explicit namespace_(const std::string& name);

        namespace_(const namespace_& source);

        /**
        @return the name of the namespace
        Anonymous namespaces return an empty string.
        */
        const std::string&
        name() const;

        /**
        @return the full name of the namespace, including all parent namespaces (e.g. ::foo::bar)
        */
        std::string
        full_name() const;

        /**
        @return true if the namespace is the global one, false otherwise
        */
        bool
        is_global() const;

        /**
        Tries to find an already declared member of this namespace.
        @tparam MemberT the type of the member to be found
        @param name the name of the member to be found
        @return a pointer to the member if found, a null pointer otherwise
        */
        template <class MemberT>
        std::shared_ptr<MemberT>
        find_member_by_name(const std::string& name) const;

        /**
        @return the namespace's member list (i.e. the list of namespaces, classes, functions, etc.)
        */
        const std::vector<std::shared_ptr<namespace_member>>&
        members() const;

        /**
        @tparam MemberT type of the members to be returned
        @return the namespace's member list of the specified type
        */
        template <class MemberT>
        const std::vector<std::shared_ptr<MemberT>>&
        members() const;

        /**
        Adds a member to the namespace.
        @tparam MemberT type of the member to be added
        @param member the member to be added
        */
        template <class MemberT>
        void
        add(std::shared_ptr<MemberT> member);

        ///@todo find better than that dirty trick
        void
        shared_this(std::shared_ptr<namespace_> ptr);

    private:
        template <class MemberT>
        std::vector<std::shared_ptr<MemberT>>&
        non_const_members();

        std::string m_name;
        std::vector<std::shared_ptr<namespace_member>> m_members;
        std::vector<std::shared_ptr<namespace_>> m_namespaces;
        std::vector<std::shared_ptr<class_>> m_classes;
        std::vector<std::shared_ptr<union_>> m_unions;
};

template <class MemberT>
std::shared_ptr<MemberT>
namespace_::find_member_by_name(const std::string& name) const
{
    ///@todo use an STL algo. instead
    std::vector<std::shared_ptr<MemberT>> member_list = members<MemberT>();
    for
    (
        typename std::vector<std::shared_ptr<MemberT>>::const_iterator i = member_list.begin();
        i != member_list.end();
        ++i
    )
    {
        std::shared_ptr<MemberT> n = *i;
        if(n->name() == name)
        {
            return n;
        }
    }

    return std::shared_ptr<MemberT>(); //return a null pointer if no namespace found
}

template <class MemberT>
void
namespace_::add(std::shared_ptr<MemberT> member)
{
    //check whether no already existing namespace has the same name
    if(find_member_by_name<MemberT>(member->name()))
    {
        throw std::runtime_error(full_name() + " already contains a member named \"" + member->name() + "\" of the same type.");
    }

    //tell namespace that we (i.e. this) are its parent
    member->parent(shared_from_this());

    //add namespace to private containers
    non_const_members<MemberT>().push_back(member);
    m_members.push_back(member);
}

template <class MemberT>
std::vector<std::shared_ptr<MemberT>>&
namespace_::non_const_members()
{
    return const_cast<std::vector<std::shared_ptr<MemberT>>&>(members<MemberT>());
}

}}} //namespace socoa::cpp::program_tree

#endif
