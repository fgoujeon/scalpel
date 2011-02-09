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

#include "merge.hpp"

namespace scalpel { namespace cpp { namespace linking { namespace detail
{

std::unique_ptr<semantic_graph>
merge(const utility::unique_ptr_vector<semantic_graph>& semantic_graphs, const entity_tree& tree)
{
	return std::unique_ptr<semantic_graph>(new semantic_graph());
}

}}}} //namespace scalpel::cpp::linking::detail

