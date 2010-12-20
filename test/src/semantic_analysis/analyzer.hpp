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

#ifndef SEMANTIC_ANALYSIS_ANALYZER_HPP
#define SEMANTIC_ANALYSIS_ANALYZER_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <memory>

namespace semantic_analysis
{

std::shared_ptr<scalpel::cpp::semantic_graph>
analyze(const std::string& source_code);

} //namespace name_lookup

#endif

