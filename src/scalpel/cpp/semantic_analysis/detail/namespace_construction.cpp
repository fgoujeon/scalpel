/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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

#include "namespace_construction.hpp"
#include "class_construction.hpp"
#include "enum_construction.hpp"
#include "function_construction.hpp"
#include "type_construction.hpp"
#include "other_entity_construction.hpp"
#include "semantic_entity_analysis/identification_policies.hpp"
#include "syntax_node_analysis/class_specifier.hpp"
#include "syntax_node_analysis/function_definition.hpp"
#include "syntax_node_analysis/declarator.hpp"
#include "syntax_node_analysis/decl_specifier_seq.hpp"

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

using namespace syntax_nodes;
using namespace semantic_entities;

utility::variant
<
	semantic_entities::namespace_*,
	semantic_entities::unnamed_namespace*
>
create_namespace
(
	const syntax_nodes::namespace_definition& namespace_definition_node
)
{
	if(const optional_node<identifier>& identifier_node = get_identifier(namespace_definition_node))
	{
		const std::string& namespace_name = identifier_node->value();
		return new namespace_(namespace_name);
	}
	else
	{
		return new unnamed_namespace();
	}
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

