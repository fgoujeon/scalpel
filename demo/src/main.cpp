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

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <scalpel/cpp/preprocessor.hpp>
#include <scalpel/cpp/syntax_analyzer.hpp>
#include <scalpel/cpp/semantic_analyzer.hpp>
#include "syntax_tree_print_functions.hpp"
#include "semantic_graph_print_functions.hpp"

int
main(int argc, char** argv)
{
	if(argc != 2)
	{
		std::cout << "Usage:\n";
		std::cout << "\t" << argv[0] << " source_file_to_be_analyzed\n";
	}

	scalpel::cpp::preprocessor preprocessor;
	scalpel::cpp::syntax_analyzer syntax_analyzer;
	scalpel::cpp::semantic_analyzer semantic_analyzer;

	std::string filename = argv[1];

	//open file
	std::ifstream file(filename.c_str());
	if(!file)
	{
		std::cout << filename << " doesn't exits.";
		return 1;
	}

	//read file
	std::ostringstream buffer;
	buffer << file.rdbuf();

	//close file
	file.close();

	std::cout << "Analyzing " << filename << "...\n";

	//preprocessing
	std::vector<std::string> include_paths =
	{
		"/usr/include",
		"/usr/include/c++/4.4.0",
		"/usr/include/c++/4.4.0/i686-pc-linux-gnu",
		"/usr/include/c++/4.4.0/parallel",
		"/usr/include/linux",
		"/usr/lib/gcc/i686-pc-linux-gnu/4.4.0/include"
	};
	std::string preprocessed_code = preprocessor(buffer.str(), include_paths);

	//syntax analysis
	scalpel::cpp::syntax_tree tree = syntax_analyzer(preprocessed_code);

	//print syntax tree
	std::cout << "Syntax tree:\n";
	print(tree);

	//semantic analysis
	scalpel::cpp::semantic_graph graph = semantic_analyzer(tree);

	//print semantic graph
	std::cout << "Semantic graph:\n";
	semantic_graph_print_functions::print(graph);

	return 0;
}

