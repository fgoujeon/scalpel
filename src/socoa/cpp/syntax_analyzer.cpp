/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

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

#include "syntax_analyzer.hpp"

#include <iostream>
#include <stdexcept>
#include <boost/spirit/tree/parse_tree.hpp>
#include "../util/raii_affector.hpp"
#include "parse_tree_to_syntax_tree.hpp"
#include "source_code_completion.hpp"
#include "semantic_graph.hpp"
#include "name_lookup.hpp"

using namespace boost::spirit;
using namespace socoa::cpp::syntax_tree;
using namespace socoa::util;

namespace socoa { namespace cpp
{

syntax_analyzer::type_name_parser::type_name_parser(syntax_analyzer& a):
    syntax_analyzer_(a)
{
}

std::ptrdiff_t
syntax_analyzer::type_name_parser::operator()(const scanner_t& scan) const
{
    return syntax_analyzer_.parse_type_name(scan);
}


syntax_analyzer::syntax_analyzer():
    type_name_parser_(*this),
	grammar_(type_name_parser_)
{
}

syntax_tree_t
syntax_analyzer::operator()(const std::string& input)
{
    input_ = &input;
    highest_parsing_progress_ = 0;
    performing_semantic_analysis_ = false;
	type_name_map_.clear();

    return analyze(input);
}

syntax_tree_t
syntax_analyzer::analyze(const std::string& input)
{
    //parse the input with the C++ grammar
    boost::spirit::tree_parse_info<> info = boost::spirit::pt_parse
    (
        input.c_str(),
        grammar_.get_start_rule(),
        boost::spirit::space_p
    );

    //throw an exception if parsing fails
    if(!info.full)
    {
        std::ostringstream failure_message;
        failure_message << "Parsing stopped at:\n***\n" << info.stop << "\n***";
        throw std::runtime_error(failure_message.str().c_str());
    }

    //convert spirit's parse tree to syntax tree
    return convert_parse_tree_to_syntax_tree(*info.trees.begin());
}

/**
 * This function is called when the grammar has to check whether a name
 * represents a type or not.
 */
std::ptrdiff_t
syntax_analyzer::parse_type_name(const scanner_t& scan)
{
    const char* parsing_progress = scan.first;

	//
	//Get the name of which type (type name or simple variable name)
	//must be checked.
	//
	std::string name;
	char ch = *scan;
	while
	(
		!scan.at_end() &&
		(
			(ch >= 'a' && ch <= 'z') ||
			(ch >= 'A' && ch <= 'Z') ||
			(ch == '_') ||
			(ch >= '0' && ch <= '9')
		)
	)
	{
		name += ch;
		++scan;
		ch = *scan;
	}

	//if we already checked that name at the same progress point, we stored the result
	if(highest_parsing_progress_ >= parsing_progress)
	{
		std::map<const char*, bool>::const_iterator is_a_type_it = type_name_map_.find(parsing_progress);
		if(is_a_type_it != type_name_map_.end())
		{
			if(is_a_type_it->second)
				return name.size(); //successful match
			else
				return -1;
		}
	}

	//if we're not already performing a semantic analysis (avoid recursive call)
	if(!performing_semantic_analysis_)
	{
		raii_affector<bool, true, false> raii_aff(performing_semantic_analysis_);

		//
		//Create a new string from the beginning of the input to the current
		//location of the scanner.
		//
		assert(input_);
		std::string partial_input(&*(input_->begin()), scan.first);


		std::cout << "\nTry to determine whether '" << name << "' is a type name...\n";
		std::cout << "Fragment of input succesfully parsed:\n";
		std::cout << "***\n" << partial_input << "\n***\n";

		//
		//Complete the scanned source code (partial_input) in order to have
		//a syntactically correct input to analyze.
		//
		unsigned int closed_scope_count = source_code_completion::complete(partial_input);
		std::cout << "Completed input:\n";
		std::cout << "***\n" << partial_input << "\n***\n";

		//
		//Analyze the source code's syntax
		//
		std::cout << "Syntax analysis:\n";
		syntax_tree_t syntax_tree = analyze(partial_input);

		//
		//Analyze the source code's semantic
		//
		std::cout << "Semantic analysis:\n";
		semantic_graph_t semantic_graph = semantic_analyzer_(syntax_tree);

		//
		//Get the scope from where to find the given type name.
		//
		semantic_graph::scope* scope = &semantic_graph;
		for(unsigned int i = 0; i < closed_scope_count; ++i)
		{
			if(!scope->get_scopes().empty()) ///\todo should be an assert when scope tree construction implementation will be full
				scope = scope->get_scopes().back();
			else
				break;
		}

		//
		//Check whether the name is really a type name.
		//
		const semantic_graph::named_item* const item = name_lookup::find_unqualified_name(*scope, name);
		if(item && item->is_a_type())
		{
			std::cout << "'" << name << "' is a type name.\n";
			type_name_map_.insert(std::make_pair<const char*, bool>(parsing_progress, true));
			return name.size(); //successful match
		}
		else
		{
			std::cout << "'" << name << "' isn't a type name.\n";
			type_name_map_.insert(std::make_pair<const char*, bool>(parsing_progress, false));
		}

        highest_parsing_progress_ = parsing_progress;
    }

    return -1;
}

}} //namespace socoa::cpp
