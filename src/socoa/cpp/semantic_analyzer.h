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

#ifndef SOCOA_CPP_SEMANTIC_ANALYZER_H
#define SOCOA_CPP_SEMANTIC_ANALYZER_H

#include <memory>
#include "semantic_graph.h"

namespace socoa { namespace cpp
{

/**
@brief Analyses the semantic of the source code of a full C++ program.
*/
class semantic_analyzer
{
    public:
		semantic_analyzer();

		const std::shared_ptr<semantic_graph_t>
		operator()(const syntax_tree_t& tree);

    private:
};

}} //namespace socoa::cpp

#endif
