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

#ifndef SINGLE_PREPROCESSING_STANDARD_LIBRARY_TEST_H
#define SINGLE_PREPROCESSING_STANDARD_LIBRARY_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <socoa/cpp/preprocessor.h>
#include <socoa/cpp/declaration_syntax_analyzer.h>

class standard_library_test: public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(standard_library_test);
    CPPUNIT_TEST(parse_files);
    CPPUNIT_TEST_SUITE_END();

    public:
        void
        parse_files();

    private:
        socoa::cpp::preprocessor m_preprocessor;
        socoa::cpp::declaration_syntax_analyzer m_declaration_syntax_analyzer;
};

#endif
