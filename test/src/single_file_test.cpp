/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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
#include <scalpel/cpp/syntax_nodes/utility/value_getter.hpp>
#include <memory>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <fstream>

using namespace boost::spirit;
using namespace std;
using scalpel::cpp::syntax_nodes::utility::get_value;

void
single_file_test::parse_files(const std::string& test_directory)
{
    const std::string directory_name("testfiles/" + test_directory);

    for(unsigned int i = 0; ; ++i)
    {
		//generate file's name
        std::ostringstream file_name_oss;
        file_name_oss << directory_name << "/test" << setfill('0') << setw(3) << i << ".cpp";

		//open file
        std::ifstream file(file_name_oss.str().c_str());
        if(!file)
        {
            if(i == 0)
                throw runtime_error("There's no file to parse in " + directory_name + ".");
            else
                break; //exit if file doesn't exist
        }

		//read file
        ostringstream buffer;
        buffer << file.rdbuf();

		//close file
        file.close();

		std::cout << "Analyzing " << file_name_oss.str() << "...\n";

		//preprocessing
		std::string preprocessed_code = preprocessor_(buffer.str(), include_paths_, macro_definitions_);

		//syntax analysis
		std::unique_ptr<scalpel::cpp::syntax_tree> tree;
		try
		{
			tree = std::move(std::unique_ptr<scalpel::cpp::syntax_tree>(new scalpel::cpp::syntax_tree(syntax_analyzer_(preprocessed_code))));
		}
		catch(...)
		{
			std::cout << "Preprocessed code of " << file_name_oss.str() << ":\n";
			std::cout << "***\n";
			std::cout << preprocessed_code;
			std::cout << "\n***\n";
			throw;
		}

		//check syntax analysis results
		if(preprocessed_code != get_value(*tree))
		{
			std::cout << "Analysis error!\n";
			std::cout << "Original content of " << file_name_oss.str() << ":\n";
			std::cout << "***\n";
			std::cout << preprocessed_code;
			std::cout << "\n***\n";
			std::cout << "Analysis results:\n";
			std::cout << "***\n";
			std::cout << get_value(*tree);
			std::cout << "\n***\n\n";

			throw "Analysis error!";
		}

		//semantic analysis
		//semantic_analyzer_(tree);
    }
}

void
single_file_test::include_paths(const std::vector<std::string>& include_paths)
{
	include_paths_ = include_paths;
}

void
single_file_test::macro_definitions(const std::vector<std::string>& macro_definitions)
{
	macro_definitions_ = macro_definitions;
}

