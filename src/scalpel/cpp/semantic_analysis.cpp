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

#include "semantic_analysis.hpp"
#include "detail/semantic_analysis/namespace_construction.hpp"
#include <iostream>
#include <stdexcept>

namespace scalpel { namespace cpp
{

namespace semantic_analysis
{

using namespace syntax_nodes;
using namespace semantic_entities;

std::shared_ptr<semantic_graph>
analyze(const syntax_tree& tree)
{
	//create semantic graph
	std::shared_ptr<namespace_> global_namespace = namespace_::make_shared();

	auto opt_declaration_seq_node = get_declaration_seq(tree);
	if(opt_declaration_seq_node)
	{
		auto declaration_seq_node = *opt_declaration_seq_node;
		detail::semantic_analysis::fill_namespace(global_namespace, declaration_seq_node);
	}

	return global_namespace;
}

} //namespace semantic_analysis

}} //namespace scalpel::cpp

