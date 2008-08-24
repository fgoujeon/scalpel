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

#ifndef CPPPARSER_PROGRAM_MODEL_NAMESPACE_MEMBER_H
#define CPPPARSER_PROGRAM_MODEL_NAMESPACE_MEMBER_H

#include <memory>

namespace cppparser { namespace program_model
{

class namespace_;

class namespace_member
{
    public:
        virtual ~namespace_member();

        bool
        has_parent() const;

        std::shared_ptr<namespace_>
        parent();

        const std::shared_ptr<namespace_>
        parent() const;

        void
        parent(std::shared_ptr<namespace_> parent);

    private:
        std::weak_ptr<namespace_> m_parent;
};

}} //namespace cppparser::program_model

#endif
