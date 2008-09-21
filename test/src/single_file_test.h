/*
Socoa - Source Code Analysis Library
Copyright © 2008  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SINGLE_FILE_TEST_H
#define SINGLE_FILE_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <socoa/cpp/declaration_syntax_analyzer.h>
#include <socoa/cpp/declaration_semantic_analyzer.h>
#include <socoa/cpp/program_syntax_tree_to_string_converter.h>

class single_file_test: public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(single_file_test);
    CPPUNIT_TEST(parse_files);
    CPPUNIT_TEST_SUITE_END();

    public:
        void
        parse_files();

    private:
        socoa::cpp::declaration_syntax_analyzer m_declaration_syntax_analyzer;
        socoa::cpp::declaration_semantic_analyzer m_declaration_semantic_analyzer;
        socoa::cpp::program_syntax_tree_to_string_converter m_program_syntax_tree_to_string_converter;
};

#endif
