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

#ifndef CPPPARSER_PARSING_CURSOR_H
#define CPPPARSER_PARSING_CURSOR_H

#include <memory>
#include "../program_model/program.h"

namespace cppparser { namespace parsing
{

class cursor
{
    public:
        cursor();

        program_model::program&
        program_model();

        std::weak_ptr<program_model::namespace_>
        current_namespace();

        void
        enter_namespace(std::weak_ptr<program_model::namespace_> a_namespace);

        void
        leave_current_namespace();

    private:
        program_model::program m_program_model;
        std::weak_ptr<program_model::namespace_> m_current_namespace;
};

}} //namespace cppparser::parsing

#endif
