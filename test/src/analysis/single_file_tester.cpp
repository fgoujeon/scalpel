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

#include "single_file_tester.hpp"
#include <cpp2xml/semantic_graph.hpp>
#include <scalpel/cpp/linking.hpp>
#include <scalpel/cpp/semantic_analysis.hpp>
#include <boost/test/unit_test.hpp>
#include <memory>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <fstream>

using namespace boost::spirit;

namespace analysis
{

void
single_file_tester::parse_file(const std::string& filename)
{
	//open file
	std::ifstream file(filename.c_str());
	if(!file)
	{
		throw std::runtime_error("There's no file named " + filename + ".");
	}

	//read file
	std::ostringstream buffer;
	buffer << file.rdbuf();

	//close file
	file.close();

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
		std::cout << "Preprocessed code of " << filename << ":\n";
		std::cout << "***\n";
		std::cout << preprocessed_code;
		std::cout << "\n***\n";
		throw;
	}
}

void
single_file_tester::test_semantic_analysis(const semantic_analysis_test_file_set& file_set)
{
	const std::string& input_filename = file_set.input_file;
	const std::string& expected_output_filename = file_set.output_file;

	//open file
	std::ifstream file(input_filename.c_str());
	if(!file)
	{
		throw std::runtime_error("There's no file named " + input_filename + ".");
	}

	//read file
	std::ostringstream buffer;
	buffer << file.rdbuf();

	//close file
	file.close();

	//preprocessing
	std::string preprocessed_code = preprocessor_(buffer.str(), include_paths_, macro_definitions_);

	//syntax analysis
	scalpel::cpp::syntax_tree syntax_tree = syntax_analyzer_(preprocessed_code);

	//semantic analysis
	std::unique_ptr<scalpel::cpp::semantic_graph> semantic_graph;
	try
	{
		semantic_graph = scalpel::cpp::semantic_analysis::analyze(syntax_tree);
	}
	catch(...)
	{
		std::cout << "Exception during the semantic analysis of '" << input_filename << "':\n";
		throw;
	}

	//serialize the semantic graph
	std::ostringstream semantic_graph_xml;
	cpp2xml::serialize_semantic_graph(*semantic_graph, semantic_graph_xml);

	//open the result file
	std::ifstream expected_output_file(expected_output_filename.c_str());
	if(!expected_output_file)
	{
		throw std::runtime_error("There's no file named " + expected_output_filename + ".");
	}

	//read the result file
	std::ostringstream expected_output_buffer;
	expected_output_buffer << expected_output_file.rdbuf();

	//close the result file
	expected_output_file.close();

	//compare the results
	BOOST_CHECK_EQUAL(semantic_graph_xml.str(), expected_output_buffer.str());
}

void
single_file_tester::test_linking(const linking_test_file_set& file_set)
{
	scalpel::utility::unique_ptr_vector<scalpel::cpp::semantic_graph> semantic_graphs;
	for(auto i = file_set.cpp_files.begin(); i != file_set.cpp_files.end(); ++i) //for each input file
	{
		const std::string& filename = *i;

		//open file
		std::ifstream file(filename.c_str());
		if(!file)
		{
			throw std::runtime_error("There's no file named " + filename + ".");
		}

		//read file
		std::ostringstream buffer;
		buffer << file.rdbuf();

		//close file
		file.close();

		//preprocessing
		std::string preprocessed_code = preprocessor_(buffer.str(), include_paths_, macro_definitions_);

		//syntax analysis
		scalpel::cpp::syntax_tree syntax_tree = syntax_analyzer_(preprocessed_code);

		//semantic analysis
		std::unique_ptr<scalpel::cpp::semantic_graph> semantic_graph;
		try
		{
			semantic_graph = scalpel::cpp::semantic_analysis::analyze(syntax_tree);
		}
		catch(...)
		{
			std::cout << "Exception during the semantic analysis of '" << filename << "':\n";
			throw;
		}

		semantic_graphs.push_back(std::move(semantic_graph));
	}

	//linking
	std::unique_ptr<scalpel::cpp::linked_semantic_graph> final_semantic_graph = scalpel::cpp::linking::link(semantic_graphs);

	//serialize the semantic graph
	std::ostringstream semantic_graph_xml;
	cpp2xml::serialize_semantic_graph(*final_semantic_graph, semantic_graph_xml);

	//open the result file
	std::ifstream expected_output_file(file_set.output_file.c_str());
	if(!expected_output_file)
	{
		throw std::runtime_error("There's no file named " + file_set.output_file + ".");
	}

	//read the result file
	std::ostringstream expected_output_buffer;
	expected_output_buffer << expected_output_file.rdbuf();

	//close the result file
	expected_output_file.close();

	//compare the results
	BOOST_CHECK_EQUAL(semantic_graph_xml.str(), expected_output_buffer.str());
}

void
single_file_tester::include_paths(const std::vector<std::string>& include_paths)
{
	include_paths_ = include_paths;
}

void
single_file_tester::macro_definitions(const std::vector<std::string>& macro_definitions)
{
	macro_definitions_ = macro_definitions;
}

} //namespace analysis

