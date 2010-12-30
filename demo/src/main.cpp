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

#include <cpp2xml/semantic_graph.hpp>
#include <cpp2xml/syntax_tree.hpp>
#include <scalpel/cpp/semantic_analysis.hpp>
#include <scalpel/cpp/syntax_analyzer.hpp>
#include <scalpel/cpp/preprocessor.hpp>
#include <boost/program_options.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

int
main(int argc, char** argv)
{
	std::vector<std::string> input_files;
	std::vector<std::string> include_paths;
	std::vector<std::string> macro_definitions;
	bool print_syntax_tree = true;
	bool print_semantic_graph = true;

	//get program options
	{
		namespace po = boost::program_options;

		po::options_description hidden_options("Hidden options");
		hidden_options.add_options()
			("input-file", po::value<std::vector<std::string>>(&input_files), "input file")
		;

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
			("no-syntax-tree", "don't print syntax tree")
			("no-semantic-graph", "don't print semantic graph")
		;

		po::options_description all_options("Allowed options");
		all_options.add(hidden_options).add(visible_options);

		po::positional_options_description p;
		p.add("input-file", -1);

		po::variables_map vm;
		po::store(po::command_line_parser(argc, argv).options(all_options).positional(p).run(), vm);
		po::notify(vm);

		if(vm.count("help") || input_files.empty())
		{
			std::cout << "Usage: " << argv[0] << " [options] input-files\n\n";
			std::cout << visible_options << "\n";
			return 0;
		}

		print_syntax_tree = !vm.count("no-syntax-tree");
		print_semantic_graph = !vm.count("no-semantic-graph");
	}

	scalpel::cpp::preprocessor preprocessor;
	scalpel::cpp::syntax_analyzer syntax_analyzer;

	for(auto i = input_files.begin(); i != input_files.end(); ++i) //for each input file
	{
		const std::string& filename = *i;

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
		std::string preprocessed_code = preprocessor(buffer.str(), include_paths, macro_definitions);

		//syntax analysis
		scalpel::cpp::syntax_tree tree = syntax_analyzer(preprocessed_code);

		//print syntax tree
		if(print_syntax_tree)
		{
			std::cout << "Syntax tree:\n";
			cpp2xml::print_syntax_tree(tree);
		}

		if(print_semantic_graph)
		{
			//semantic analysis
			std::shared_ptr<const scalpel::cpp::semantic_graph> graph = scalpel::cpp::semantic_analysis::analyze(tree);

			//print semantic graph
			std::cout << "Semantic graph:\n";
			cpp2xml::serialize_semantic_graph(graph, std::cout);
		}
	}

	return 0;
}

