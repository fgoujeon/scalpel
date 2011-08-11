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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_ENUM_CONSTRUCTION_IPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_ENUM_CONSTRUCTION_IPP

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

template<class Enum>
void
fill_enum
(
	Enum& enum_entity,
	const syntax_nodes::enum_specifier& enum_specifier_node
)
{
	int value_counter = 0;

	if(const syntax_nodes::optional_node<syntax_nodes::enumerator_list>& opt_enumerator_list_node = get_enumerator_list(enum_specifier_node))
	{
		const syntax_nodes::enumerator_list& enumerator_list_node = *opt_enumerator_list_node;
		for(auto i = enumerator_list_node.begin(); i != enumerator_list_node.end(); ++i)
		{
			const syntax_nodes::enumerator_definition& enumerator_definition_node = *i;

			//create the enum constant
			std::unique_ptr<semantic_entities::enum_constant<int>> new_enum_constant
			(
				new semantic_entities::enum_constant<int>
				(
					get_identifier(enumerator_definition_node).value(),
					value_counter++
				)
			);

			//add it to the enum
			semantic_entities::enum_constant_list<int>& constant_list = utility::get<semantic_entities::enum_constant_list<int>>(enum_entity.constants());
			constant_list.add(std::move(new_enum_constant));
		}
	}
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#endif

