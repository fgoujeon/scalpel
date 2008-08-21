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
#include "namespace_item.h"

namespace cppparser { namespace program_model
{

class class_;
class enum_;
class typedef_;

/**
Represents a C++ namespace.
*/
class namespace_: public namespace_item
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
        @return the full name of the namespace, including all parents (e.g. ::foo::bar).
        */
        std::string
        full_name() const;

        /**
        @return true if the namespace is the global one, false otherwise.
        */
        bool
        is_global() const;

        /**
        Check whether an already declared symbol has the given name.
        @param name the name of the namespace to search.
        @return true if an already existing namespace has the same name, false otherwise.
        */
        std::shared_ptr<namespace_>
        find_namespace(const std::string& name) const;

        /**
        @return the item list of the namespace, i.e. the list of classes, function, etc.
        */
        const std::vector<std::shared_ptr<namespace_item>>&
        items() const;

        /*void
        add(std::shared_ptr<namespace_item> a_namespace_item);*/

        void
        add(std::shared_ptr<namespace_> a_namespace);

        ///@todo find better than that dirty trick
        void
        shared_this(std::shared_ptr<namespace_> ptr);

    private:
        std::string m_name;
        std::shared_ptr<namespace_> m_shared_this;
        std::vector<std::shared_ptr<namespace_item>> m_items;
        std::vector<std::shared_ptr<namespace_>> m_namespaces;
};

}} //namespace cppparser::program_model

#endif