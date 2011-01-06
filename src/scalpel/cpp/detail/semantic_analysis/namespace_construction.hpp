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

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_NAMESPACE_CONSTRUCTION_HPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_NAMESPACE_CONSTRUCTION_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/cpp/syntax_tree.hpp>
#include <memory>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

std::shared_ptr<semantic_entities::namespace_>
create_namespace
(
	const syntax_nodes::namespace_definition& namespace_definition_node
);

void
fill_namespace
(
	std::shared_ptr<semantic_entities::namespace_> namespace_entity,
	const syntax_nodes::namespace_definition& namespace_definition_node
);

void
fill_namespace
(
	std::shared_ptr<semantic_entities::namespace_> namespace_entity,
	const syntax_nodes::simple_declaration& simple_declaration_node
);

void
fill_namespace
(
	std::shared_ptr<semantic_entities::namespace_> namespace_entity,
	const syntax_nodes::declaration_seq& declaration_seq_node
);

void
fill_namespace
(
	std::shared_ptr<semantic_entities::namespace_> namespace_entity,
	const syntax_nodes::function_definition& function_definition_node
);

//Check whether the given class hasn't been forward declared in the given
//namespace.
//If so, return the forward declared class.
//If not, add the given class to the given namespace and return the given class.
std::shared_ptr<semantic_entities::class_>
add_class
(
	const std::shared_ptr<semantic_entities::namespace_>& namespace_entity,
	const std::shared_ptr<semantic_entities::class_>& class_entity
);

}}}} //namespace scalpel::cpp::detail::semantic_analysis

#endif

