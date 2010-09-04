/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#define BOOST_TEST_ALTERNATIVE_INIT_API //don't use legacy API

#include "variant/exception_safety_test_case.hpp"
#include "name_lookup/test_case_1.hpp"
#include "name_lookup/test_case_2.hpp"
#include "name_lookup/test_case_3.hpp"
#include "name_lookup/test_case_4.hpp"
#include "name_lookup/test_case_5.hpp"
#include "name_lookup/test_case_6.hpp"
#include "name_lookup/test_case_7.hpp"
#include "name_lookup/test_case_8.hpp"
#include "name_lookup/test_case_9.hpp"
#include "name_lookup/test_case_10.hpp"
#include "syntax_analysis/single_file_tester.hpp"
#include "get_recursive_file_list.hpp"
#include <boost/program_options.hpp>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>
#include <boost/bind.hpp>
#include <iostream>

using namespace boost::unit_test;

syntax_analysis::single_file_tester syntax_analysis_single_file_tester;

bool
init_unit_test()
{
	//
	//Initialization
	//

	std::vector<std::string> include_paths;
	std::vector<std::string> macro_definitions;

	//get program options
	{
		namespace po = boost::program_options;

		po::options_description visible_options("Visible options");
		visible_options.add_options()
			("help,h", "produce help message")
			("include-path,I", po::value<std::vector<std::string>>(&include_paths), "include path")
			(
				"macro-definition,D",
				po::value<std::vector<std::string>>(&macro_definitions),
				"Macro definition. Possible formats:\n"
				"\"MACRO\" define MACRO as 1\n"
				"\"MACRO=\" define MACRO as nothing (empty)\n"
				"\"MACRO=definition\" define MACRO as definition\n"
				"\"MACRO(x)\" define MACRO(x) as 1\n"
				"\"MACRO(x)=\" define MACRO(x) as nothing (empty)\n"
				"\"MACRO(x)=definition\" define MACRO(x) as definition"
			)
		;

		po::options_description all_options("Allowed options");
		all_options.add(visible_options);

		po::variables_map vm;
		po::store(po::command_line_parser(framework::master_test_suite().argc, framework::master_test_suite().argv).options(all_options).run(), vm);
		po::notify(vm);

		if(vm.count("help"))
		{
			std::cout << "Usage: " << framework::master_test_suite().argv[0] << " [options]\n\n";
			std::cout << visible_options << "\n";
			return 0;
		}
	}

	syntax_analysis_single_file_tester.include_paths(include_paths);
	syntax_analysis_single_file_tester.macro_definitions(macro_definitions);



	//
	//Syntax analysis test suite
	//

	//build test file list
	std::vector<std::string> test_files = get_recursive_file_list("test/testfiles");

	//add the syntax analysis test cases (one per test file) to the master test suite
	boost::callback1<std::string> tm = boost::bind(&syntax_analysis::single_file_tester::parse_file, &syntax_analysis_single_file_tester, _1);
    framework::master_test_suite().add(BOOST_PARAM_TEST_CASE(tm, test_files.begin(), test_files.end()));



	//
	//Name lookup test suite
	//

    framework::master_test_suite().add(BOOST_TEST_CASE(&name_lookup::test_case_1));
    framework::master_test_suite().add(BOOST_TEST_CASE(&name_lookup::test_case_2));
    framework::master_test_suite().add(BOOST_TEST_CASE(&name_lookup::test_case_3));
    framework::master_test_suite().add(BOOST_TEST_CASE(&name_lookup::test_case_4));
    framework::master_test_suite().add(BOOST_TEST_CASE(&name_lookup::test_case_5));
    framework::master_test_suite().add(BOOST_TEST_CASE(&name_lookup::test_case_6));
    framework::master_test_suite().add(BOOST_TEST_CASE(&name_lookup::test_case_7));
    framework::master_test_suite().add(BOOST_TEST_CASE(&name_lookup::test_case_8));
    framework::master_test_suite().add(BOOST_TEST_CASE(&name_lookup::test_case_9));
    framework::master_test_suite().add(BOOST_TEST_CASE(&name_lookup::test_case_10));



	//
	//Variant test suite
	//

    framework::master_test_suite().add(BOOST_TEST_CASE(&variant::exception_safety_test_case));

    return true;
}

