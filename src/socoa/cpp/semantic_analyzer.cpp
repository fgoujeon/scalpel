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

#include "semantic_analyzer.hpp"

namespace socoa { namespace cpp
{

semantic_analyzer::semantic_analyzer()
{
}

semantic_graph_t
semantic_analyzer::operator()(const syntax_tree_t& tree)
{
	//create global namespace
	semantic_graph_t global_namespace;
	semantic_graph_ = &global_namespace;

	return global_namespace;
}

}} //namespace socoa::cpp

