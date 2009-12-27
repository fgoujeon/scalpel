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

#include "single_file_test.hpp"
#include <boost/program_options.hpp>
#include <boost/test/included/unit_test.hpp>
#include <boost/bind.hpp>
#include <iostream>

using namespace boost::unit_test;

single_file_test t;



BOOST_AUTO_TEST_SUITE(test_suite1)

BOOST_AUTO_TEST_CASE(basic_test_case)
{
	t.parse_files("basic");
}

BOOST_AUTO_TEST_CASE(name_lookup_test_case)
{
	t.parse_files("name_lookup");
}

BOOST_AUTO_TEST_CASE(template_test_case)
{
	t.parse_files("template");
}

BOOST_AUTO_TEST_CASE(ambiguous_cases_test_case)
{
	t.parse_files("ambiguous_cases");
}

BOOST_AUTO_TEST_CASE(standard_library_test_case)
{
	t.parse_files("standard_library");
}

BOOST_AUTO_TEST_SUITE_END()



test_suite*
init_unit_test_suite(int argc, char** argv)
{
    framework::master_test_suite().p_name.value = "Master test suite";

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
		po::store(po::command_line_parser(argc, argv).options(all_options).run(), vm);
		po::notify(vm);

		if(vm.count("help"))
		{
			std::cout << "Usage: " << argv[0] << " [options]\n\n";
			std::cout << visible_options << "\n";
			return 0;
		}
	}

	t.include_paths(include_paths);
	t.macro_definitions(macro_definitions);

    return 0;
}

