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

#ifndef CPPPARSER_PROGRAM_MODEL_CLASS_H
#define CPPPARSER_PROGRAM_MODEL_CLASS_H

#include "type.h"
#include "namespace_member.h"

namespace cppparser { namespace program_model
{

class class_: public type, public namespace_member
{
    public:
        /**
        Creates a named class.
        @param name the class' name
        */
        explicit class_(const std::string& name);

        ///@todo find better than that dirty trick
        void
        shared_this(std::shared_ptr<class_> ptr);

    private:
        std::shared_ptr<class_> m_shared_this;
};

}} //namespace cppparser::program_model

#endif
