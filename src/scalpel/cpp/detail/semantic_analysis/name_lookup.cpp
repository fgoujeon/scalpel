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

#include "name_lookup.hpp"

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis { namespace name_lookup
{

semantic_entities::declarative_region_shared_ptr_variant
impl::find_declarative_region
(
	const syntax_nodes::nested_identifier_or_template_id& nested_identifier_or_template_id_node,
	const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region
)
{
	auto opt_nested_name_specifier_node = get_nested_name_specifier(nested_identifier_or_template_id_node);

	if(has_leading_double_colon(nested_identifier_or_template_id_node))
	{
		//the first declarative region is in the global namespace
		semantic_entities::declarative_region_shared_ptr_variant global_namespace = current_declarative_region;
		while(has_declarative_region(global_namespace))
		{
			global_namespace = get_declarative_region(global_namespace);
		}

		if(opt_nested_name_specifier_node)
		{
			auto nested_name_specifier_node = *opt_nested_name_specifier_node;

			//find the first declarative region
			auto identifier_or_template_id_node = get_identifier_or_template_id(nested_name_specifier_node);
			semantic_entities::declarative_region_shared_ptr_variant first_declarative_region =
				find_entities_in_declarative_region<false, false, semantic_entities::declarative_region_shared_ptr_variant>(identifier_or_template_id_node, global_namespace)
			;

			//find the last declarative region
			return find_declarative_region(nested_name_specifier_node, first_declarative_region);
		}
		else
		{
			//both the first and last declarative regions ARE the global namespace
			return global_namespace;
		}
	}
	else
	{
		if(opt_nested_name_specifier_node)
		{
			auto nested_name_specifier_node = *opt_nested_name_specifier_node;

			//find the first declarative region
			auto identifier_or_template_id_node = get_identifier_or_template_id(nested_name_specifier_node);
			semantic_entities::declarative_region_shared_ptr_variant first_declarative_region =
				find_entities<false, false, semantic_entities::declarative_region_shared_ptr_variant>(identifier_or_template_id_node, current_declarative_region)
			;

			//find the last declarative region
			return find_declarative_region(nested_name_specifier_node, first_declarative_region);
		}
		else
		{
			assert(false); //case already handled
		}
	}
}

semantic_entities::declarative_region_shared_ptr_variant
impl::find_declarative_region
(
	const syntax_nodes::nested_name_specifier& nested_name_specifier_node,
	const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region
)
{
	if(auto opt_last_part_seq_node = get_last_part_seq(nested_name_specifier_node))
	{
		auto last_part_seq_node = *opt_last_part_seq_node;

		semantic_entities::declarative_region_shared_ptr_variant found_declarative_region = current_declarative_region;
		for
		(
			auto i = last_part_seq_node.begin();
			i != last_part_seq_node.end();
			++i
		)
		{
			const syntax_nodes::nested_name_specifier_last_part& last_part_node = i->main_node();
			if(has_template_keyword(last_part_node))
			{
				assert(false); //not implemented yet (template)
			}
			else
			{
				const syntax_nodes::identifier_or_template_id& identifier_or_template_id_node = get_identifier_or_template_id(last_part_node);
				if(auto opt_identifier_node = syntax_nodes::get<syntax_nodes::identifier>(&identifier_or_template_id_node))
				{
					auto identifier_node = *opt_identifier_node;
					found_declarative_region =
						find_entities_from_identifier_in_declarative_region<false, false, semantic_entities::declarative_region_shared_ptr_variant>
						(
							identifier_node.value(),
							found_declarative_region
						)
					;
				}
				else
				{
					assert(false); //not implemented yet (template)
				}
			}
		}

		return found_declarative_region;
	}
	else
	{
		return current_declarative_region;
	}
}

}}}}} //namespace scalpel::cpp::detail::semantic_analysis::name_lookup

