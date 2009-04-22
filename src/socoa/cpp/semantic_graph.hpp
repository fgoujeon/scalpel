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

#ifndef SOCOA_CPP_SEMANTIC_GRAPH_HPP
#define SOCOA_CPP_SEMANTIC_GRAPH_HPP

#include "semantic_nodes/namespace_.hpp"
#include "semantic_nodes/class_.hpp"
#include "semantic_nodes/function.hpp"

namespace socoa { namespace cpp
{

typedef semantic_nodes::namespace_ semantic_graph;

}} //namespace socoa::cpp

#endif
