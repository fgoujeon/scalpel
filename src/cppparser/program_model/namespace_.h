/*
CppParser - Standard C++ programming language parsing library
Copyright © 2008  Florian Goujeon

This file is part of CppParser.

CppParser is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

CppParser is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with CppParser.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CPPPARSER_PROGRAM_MODEL_NAMESPACE_H
#define CPPPARSER_PROGRAM_MODEL_NAMESPACE_H

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include "namespace_member.h"

namespace cppparser { namespace program_model
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
        @param name the namespace's name.
        */
        explicit namespace_(const std::string& name);

        /**
        Destructor.
        */
        ~namespace_();

        /**
        @return the name of the namespace.
        Anonymous namespaces return an empty string.
        */
        const std::string&
        name() const;

        /**
        @return the full name of the namespace, including all parent namespaces (e.g. ::foo::bar).
        */
        std::string
        full_name() const;

        /**
        @return true if the namespace is the global one, false otherwise.
        */
        bool
        is_global() const;

        /**
        Find an already declared member which has the given name.
        @param name the name of the member to search.
        @return a pointer to the member if found, a null pointer otherwise.
        */
        template <class MemberT>
        std::shared_ptr<namespace_>
        find_member(const std::string& name) const;

        /**
        @return the member list of the namespace, i.e. the list of namespaces, classes, functions, etc.
        */
        const std::vector<std::shared_ptr<namespace_member>>&
        members() const;

        template <class MemberT>
        void
        add(std::shared_ptr<MemberT> member);

        ///@todo find better than that dirty trick
        void
        shared_this(std::shared_ptr<namespace_> ptr);

    private:
        template <class MemberT>
        const std::vector<std::shared_ptr<MemberT>>&
        specific_members() const;

        template <class MemberT>
        std::vector<std::shared_ptr<MemberT>>&
        non_const_specific_members();

        std::string m_name;
        std::shared_ptr<namespace_> m_shared_this;
        std::vector<std::shared_ptr<namespace_member>> m_members;
        std::vector<std::shared_ptr<namespace_>> m_namespaces;
};

template <class MemberT>
std::shared_ptr<namespace_>
namespace_::find_member(const std::string& name) const
{
    ///@todo use STL algo. instead
    std::vector<std::shared_ptr<MemberT>> members = specific_members<MemberT>();
    for
    (
        typename std::vector<std::shared_ptr<MemberT>>::const_iterator i = members.begin();
        i != members.end();
        ++i
    )
    {
        std::shared_ptr<MemberT> n = *i;
        if(n->name() == name)
        {
            return n;
        }
    }

    return std::shared_ptr<namespace_>(); //return a null pointer if no namespace found
}

template <class MemberT>
void
namespace_::add(std::shared_ptr<MemberT> member)
{
    //check whether no already existing namespace has the same name
    if(find_member<MemberT>(member->name()))
    {
        throw std::runtime_error(full_name() + " already contains a member named \"" + member->name() + "\" of the same type.");
    }

    //tell namespace that we (i.e. this) are its parent
    //member->parent(shared_from_this());
    member->parent(m_shared_this);
    member->shared_this(member); ///< @todo find better than that dirty trick

    //add namespace to private containers
    non_const_specific_members<MemberT>().push_back(member);
    m_members.push_back(member);
}

template <class MemberT>
std::vector<std::shared_ptr<MemberT>>&
namespace_::non_const_specific_members()
{
    return const_cast<std::vector<std::shared_ptr<MemberT>>&>(specific_members<MemberT>());
}

}} //namespace cppparser::program_model

#endif
