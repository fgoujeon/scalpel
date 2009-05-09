/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SINGLE_PREPROCESSING_STANDARD_LIBRARY_TEST_HPP
#define SINGLE_PREPROCESSING_STANDARD_LIBRARY_TEST_HPP

#include <scalpel/cpp/preprocessor.hpp>
#include <scalpel/cpp/syntax_analyzer.hpp>

class standard_library_test
{
    public:
        void
        parse_files();

    private:
        scalpel::cpp::preprocessor m_preprocessor;
        scalpel::cpp::syntax_analyzer m_syntax_analyzer;
};

#endif
