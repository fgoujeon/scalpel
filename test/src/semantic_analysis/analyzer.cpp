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

#include "analyzer.hpp"
#include <scalpel/cpp/semantic_analysis.hpp>
#include <scalpel/cpp/syntax_analyzer.hpp>
#include <scalpel/cpp/preprocessor.hpp>

namespace semantic_analysis
{

std::shared_ptr<scalpel::cpp::semantic_graph>
analyze(const std::string& source_code)
{
	scalpel::cpp::preprocessor preprocessor;
	scalpel::cpp::syntax_analyzer syntax_analyzer;

	//preprocessing
	const std::string preprocessed_code = preprocessor(source_code + '\n', {}, {});

	//syntax analysis
	scalpel::cpp::syntax_tree tree = syntax_analyzer(preprocessed_code);

	//semantic analysis
	return scalpel::cpp::semantic_analysis::analyze(tree);
}

} //namespace name_lookup

