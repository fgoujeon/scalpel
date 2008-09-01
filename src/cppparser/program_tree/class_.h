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

#ifndef CPPPARSER_PROGRAM_TREE_CLASS_H
#define CPPPARSER_PROGRAM_TREE_CLASS_H

#include "type.h"
#include "namespace_member.h"

namespace cppparser { namespace program_tree
{

class class_: public type, public namespace_member, public std::enable_shared_from_this<class_>
{
    public:
        /**
        Creates a named class.
        @param name the class' name
        */
        explicit class_(const std::string& name);
};

}} //namespace cppparser::program_tree

#endif
