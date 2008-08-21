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

#ifndef SINGLE_DECLARATION_TEST_H
#define SINGLE_DECLARATION_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppparser/grammar.h>

class single_declaration_test: public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(single_declaration_test);
    CPPUNIT_TEST(parse_well_formed_expressions);
    CPPUNIT_TEST(parse_ill_formed_expressions);
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();
        void parse_well_formed_expressions();
        void parse_ill_formed_expressions();

    private:
        cppparser::grammar m_grammar;
        std::vector<std::string> well_formed_expressions;
        std::vector<std::string> ill_formed_expressions;
};

#endif
