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

#include "enum_construction.hpp"
#include "syntax_node_analysis/enum_specifier.hpp"

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

using namespace syntax_nodes;
using namespace semantic_entities;

std::unique_ptr<enum_>
create_enum(const enum_specifier& enum_specifier_node)
{
	return std::unique_ptr<enum_>(new enum_(syntax_node_analysis::get_identifier(enum_specifier_node)));
}

void
fill_enum
(
	semantic_entities::enum_& enum_entity,
	const syntax_nodes::enum_specifier& enum_specifier_node
)
{
	int value_counter = 0;

	if(const optional_node<enumerator_list>& opt_enumerator_list_node = get_enumerator_list(enum_specifier_node))
	{
		const enumerator_list& enumerator_list_node = *opt_enumerator_list_node;
		for(auto i = enumerator_list_node.begin(); i != enumerator_list_node.end(); ++i)
		{
			const enumerator_definition& enumerator_definition_node = i->main_node();
			enum_entity.add
			(
				std::unique_ptr<enum_::constant>
				(
					new enum_::constant
					(
						get_identifier(enumerator_definition_node).value(),
						value_counter++
					)
				)
			);
		}
	}
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

