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

#ifndef ANALYSIS_SINGLE_FILE_TESTER_HPP
#define ANALYSIS_SINGLE_FILE_TESTER_HPP

#include "linking_test_file_set.hpp"
#include <scalpel/cpp/preprocessor.hpp>
#include <scalpel/cpp/syntax_analyzer.hpp>

namespace analysis
{

class single_file_tester
{
    public:
        void
        parse_file(const std::string& filename);

        void
        test_semantic_analysis(const std::string& filename);

        void
        test_linking(const linking_test_file_set& file_set);

		void
		include_paths(const std::vector<std::string>& include_paths);

		void
		macro_definitions(const std::vector<std::string>& macro_definitions);

    private:
		std::vector<std::string> include_paths_;
		std::vector<std::string> macro_definitions_;
        scalpel::cpp::preprocessor preprocessor_;
        scalpel::cpp::syntax_analyzer syntax_analyzer_;
};

} //namespace analysis

#endif

