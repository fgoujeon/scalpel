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

#ifndef CPPPARSER_NAMESPACE_H
#define CPPPARSER_NAMESPACE_H

#include <string>
#include <list>
#include "namespace_item.h"

namespace cppparser
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
        Creates an anonymous namespace.
        */
        namespace_();

        /**
        Creates a named namespace.
        @param name the namespace's name.
        */
        namespace_(const std::string& name);

        /**
        @return the name of the namespace.
        Anonymous namespaces return an empty string.
        */
        const std::string& name() const;

        /**
        @return the item list of the namespace, i.e. the list of classes, function, etc.
        */
        const std::list<namespace_item*>& items() const;

        void add(namespace_& a_namespace);
        void add(class_& a_class);
        void add(enum_& an_enum);
        void add(typedef_& a_typedef);

    private:
        std::string m_name;
        std::list<namespace_item*> m_items;
};

}

#endif
