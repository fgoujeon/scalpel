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

#ifndef SINGLE_FILE_TEST_H
#define SINGLE_FILE_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppparser/grammar.h>

class single_file_test: public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(single_file_test);
    CPPUNIT_TEST(parse_files);
    CPPUNIT_TEST_SUITE_END();

    public:
        single_file_test();

        void
        parse_files();

    private:
        cppparser::grammar::configuration m_grammar_configuration;
        cppparser::grammar m_grammar;
};

#endif
