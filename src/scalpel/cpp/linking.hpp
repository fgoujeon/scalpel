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

#ifndef SCALPEL_CPP_LINKING_HPP
#define SCALPEL_CPP_LINKING_HPP

#include "semantic_graph.hpp"
#include <scalpel/utility/unique_ptr_vector.hpp>
#include <memory>

namespace scalpel { namespace cpp
{

namespace linking
{

std::unique_ptr<semantic_graph>
link(const utility::unique_ptr_vector<semantic_graph>& semantic_graphs);

} //namespace semantic_analysis

}} //namespace scalpel::cpp

#endif

