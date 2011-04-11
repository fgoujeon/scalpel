/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

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

#include "analysis/single_file_tester.hpp"
#include "analysis/linkage_test_file_set.hpp"
#include "analysis/semantic_analysis_test_file_set.hpp"
#include "get_file_list.hpp"
#include <boost/program_options.hpp>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>
#include <boost/bind.hpp>
#include <iostream>

using namespace boost::unit_test;

analysis::single_file_tester analysis_single_file_tester;

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

	analysis_single_file_tester.include_paths(include_paths);
	analysis_single_file_tester.macro_definitions(macro_definitions);

	//Syntax analysis test suite
	{
		//build test file list
		std::vector<std::string> syntax_analysis_test_files = get_file_list("test/testfiles/syntax_analysis", boost::regex(".*\\.cpp"), true);

		//add the syntax analysis test cases (one per test file) to the master test suite
		boost::callback1<std::string> tm = boost::bind(&analysis::single_file_tester::parse_file, &analysis_single_file_tester, _1);
		framework::master_test_suite().add(BOOST_PARAM_TEST_CASE(tm, syntax_analysis_test_files.begin(), syntax_analysis_test_files.end()));
	}

	//Semantic analysis test suite
	{
		std::vector<analysis::semantic_analysis_test_file_set> test_files;

		//fill the test file list with testfiles/semantic_analysis files
		{
			std::vector<std::string> output_files = get_file_list("test/testfiles/semantic_analysis", boost::regex(".*\\.cpp.out"));

			for(auto i = output_files.begin(); i != output_files.end(); ++i) //for each output file...
			{
				const std::string output_file_name = *i;
				const std::string input_file_name = output_file_name.substr(0, output_file_name.length() - 4);

				//create a file set and add it to the list
				test_files.push_back
				(
					analysis::semantic_analysis_test_file_set
					{
						input_file_name,
						output_file_name
					}
				);
			}
		}

		//create the semantic analysis test cases (one per file set) and add them to the master test suite
		boost::callback1<analysis::semantic_analysis_test_file_set> tm =
			boost::bind(&analysis::single_file_tester::test_semantic_analysis, &analysis_single_file_tester, _1)
		;
		framework::master_test_suite().add(BOOST_PARAM_TEST_CASE(tm, test_files.begin(), test_files.end()));
	}

	//Linking test suite
	{
		std::vector<analysis::linkage_test_file_set> test_files;

		//fill the test file list with testfiles/linkage files
		{
			//find all output files
			std::vector<std::string> output_files = get_file_list("test/testfiles/linkage", boost::regex(".*\\.out"));

			for(auto i = output_files.begin(); i != output_files.end(); ++i) //for each output file...
			{
				const std::string output_file_name = *i;
				const std::string base_file_name = output_file_name.substr(0, output_file_name.length() - 4);

				//find the corresponding CPP input files
				std::vector<std::string> input_file_names = get_file_list("test/testfiles/linkage", boost::regex(base_file_name + "\\..*\\.cpp"));

				//create a file set and add it to the list
				test_files.push_back
				(
					analysis::linkage_test_file_set
					{
						input_file_names,
						output_file_name
					}
				);
			}
		}

		//fill the test file list with testfiles/semantic_analysis files (for single-file linkage tests)
		{
			std::vector<std::string> output_files = get_file_list("test/testfiles/semantic_analysis", boost::regex(".*\\.cpp.out"));

			for(auto i = output_files.begin(); i != output_files.end(); ++i) //for each output file...
			{
				const std::string output_file_name = *i;
				const std::string input_file_name = output_file_name.substr(0, output_file_name.length() - 4);

				//create a file set and add it to the list
				test_files.push_back
				(
					analysis::linkage_test_file_set
					{
						{input_file_name},
						output_file_name
					}
				);
			}
		}

		//create the linkage test cases (one per file set) and add them to the master test suite
		boost::callback1<analysis::linkage_test_file_set> tm = boost::bind(&analysis::single_file_tester::test_linkage, &analysis_single_file_tester, _1);
		framework::master_test_suite().add(BOOST_PARAM_TEST_CASE(tm, test_files.begin(), test_files.end()));
	}

	//Emit warning for skipped test files
	{
		std::vector<std::string> syntax_analysis_skipped_test_files = get_file_list("test/testfiles/syntax_analysis", boost::regex(".*\\.skip"), true);
		std::vector<std::string> semantic_analysis_skipped_test_files = get_file_list("test/testfiles/semantic_analysis", boost::regex(".*\\.skip"), true);
		if(!syntax_analysis_skipped_test_files.empty() || !semantic_analysis_skipped_test_files.empty())
		{
			std::cout << "Warning: the following test files will be skipped, because they're supposed to highlight known bugs. ";
			std::cout << "Remove the '.skip' extension to add them back to the test suite.\n";
			for(auto i = syntax_analysis_skipped_test_files.begin(); i != syntax_analysis_skipped_test_files.end(); ++i)
				std::cout << "- " << *i << "\n";
			for(auto i = semantic_analysis_skipped_test_files.begin(); i != semantic_analysis_skipped_test_files.end(); ++i)
				std::cout << "- " << *i << "\n";
			std::cout << "\n";
		}
	}

    return true;
}

