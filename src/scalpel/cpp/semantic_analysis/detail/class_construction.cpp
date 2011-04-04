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

#include "class_construction.hpp"
#include "function_construction.hpp"
#include "type_construction.hpp"
#include "other_entity_construction.hpp"
#include "name_lookup.hpp"
#include "semantic_entity_analysis/identification_policies.hpp"
#include "syntax_node_analysis/type_specifier_seq.hpp"

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

using namespace syntax_nodes;
using namespace semantic_entities;

std::unique_ptr<class_>
create_class(const syntax_nodes::class_specifier& class_specifier_node)
{
	return std::unique_ptr<class_>(new class_(syntax_node_analysis::get_identifier(class_specifier_node)));
}

std::unique_ptr<member_class>
create_member_class(const syntax_nodes::class_specifier& class_specifier_node, const member_access access)
{
	return
		std::unique_ptr<member_class>
		(
			new member_class
			(
				syntax_node_analysis::get_identifier(class_specifier_node),
				access
			)
		)
	;
}

std::unique_ptr<class_>
create_class
(
	const syntax_nodes::class_elaborated_specifier& class_elaborated_specifier_node
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	//get the name of the class
	std::string class_name;
	const identifier_or_template_id& identifier_or_template_id_node = get_identifier_or_template_id(class_elaborated_specifier_node);

	if(const boost::optional<const identifier&> opt_identifier_node = get<identifier>(&identifier_or_template_id_node))
	{
		class_name = opt_identifier_node->value();
	}

	//create the class
	assert(class_name != "");
	return std::unique_ptr<class_>(new class_(class_name));
}

std::unique_ptr<member_class>
create_member_class
(
	const syntax_nodes::class_elaborated_specifier& class_elaborated_specifier_node,
	const member_access access
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	//get the name of the class
	std::string class_name;
	const identifier_or_template_id& identifier_or_template_id_node = get_identifier_or_template_id(class_elaborated_specifier_node);

	if(const boost::optional<const identifier&> opt_identifier_node = get<identifier>(&identifier_or_template_id_node))
	{
		class_name = opt_identifier_node->value();
	}

	//create the class
	assert(class_name != "");
	return std::unique_ptr<member_class>(new member_class(class_name, access));
}

semantic_entities::class_ptr_variant
find_class
(
	const ptr_to_member_operator& ptr_to_member_operator_node,
	const declarative_region_ptr_variant& current_declarative_region
)
{
	const bool has_leading_double_colon = syntax_nodes::has_leading_double_colon(ptr_to_member_operator_node);

	const nested_name_specifier& nested_name_specifier_node =
		get_nested_name_specifier(ptr_to_member_operator_node)
	;


	//
	//convert nested_name_specifier -> (nested_name_specifier without last identifier) + last identifier
	//

	const optional_node<nested_name_specifier_last_part_seq>& opt_last_part_seq_node =
		get_last_part_seq(nested_name_specifier_node)
	;

	//get the last identifier
	identifier_or_template_id nested_name_specifier_last_identifier =
		opt_last_part_seq_node ?
		get_identifier_or_template_id((*opt_last_part_seq_node)[opt_last_part_seq_node->size() - 1]) :
		get_identifier_or_template_id(nested_name_specifier_node)
	;

	//create a nested-name-specifier without the last identifier
	optional_node<nested_name_specifier> opt_new_nested_name_specifier_node;
	if(opt_last_part_seq_node)
	{
		//copy the last-part by omitting the last node (i.e. the last identifier)
		const nested_name_specifier_last_part_seq& last_part_seq_node = *opt_last_part_seq_node;
		nested_name_specifier_last_part_seq new_last_part_seq_node;
		for(unsigned int i = 0; i < last_part_seq_node.size() - 1; ++i)
		{
			new_last_part_seq_node.push_back
			(
				last_part_seq_node[i]
			);
		}

		//create the nested-name-specifier node
		identifier_or_template_id new_identifier_or_template_id_node = get_identifier_or_template_id(nested_name_specifier_node);
		opt_new_nested_name_specifier_node =
			nested_name_specifier
			(
				std::move(new_identifier_or_template_id_node),
				predefined_text_node<str::double_colon>(),
				optional_node<nested_name_specifier_last_part_seq>()
			)
		;
	}


	std::string last_identifier;
	if(const boost::optional<const identifier&> opt_identifier_node = get<identifier>(&nested_name_specifier_last_identifier))
	{
		last_identifier = opt_identifier_node->value();
	}
	else
	{
		assert(false); //not managed yet
	}

	return
		name_lookup::find<semantic_entity_analysis::identification_policies::by_name, false, false, class_, member_class>
		(
			has_leading_double_colon,
			opt_new_nested_name_specifier_node,
			last_identifier,
			current_declarative_region
		)
	;
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

