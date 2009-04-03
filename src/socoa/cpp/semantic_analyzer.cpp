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

#include "semantic_analyzer.hpp"

#include <iostream>

namespace socoa { namespace cpp
{

using namespace syntax_tree;
using namespace semantic_graph;

semantic_analyzer::semantic_analyzer():
	conversion_helper_(*this)
{
}

semantic_graph_t
semantic_analyzer::operator()(const syntax_tree_t& tree)
{
	//create global namespace
	semantic_graph_t global_namespace;

	//current scope = global namespace
	scope_cursor_.set_scope(global_namespace);

	convert(tree);

	return global_namespace;
}

void
semantic_analyzer::convert(const class_head& item)
{
}

void
semantic_analyzer::convert(const class_specifier& item)
{
	boost::optional<const identifier&> id = item.get_class_head().get_identifier();

	if(id)
	{
		scope_cursor_.add_to_current_scope(class_(id->get_value()));
	}
}

void
semantic_analyzer::convert(const conversion_function_id&)
{
}

void
semantic_analyzer::convert(const ctor_initializer& item)
{
}

void
semantic_analyzer::convert(const cv_qualifier& item)
{
}

void
semantic_analyzer::convert(const declarator& item)
{
}

void
semantic_analyzer::convert(const destructor_name&)
{
}

void
semantic_analyzer::convert(const direct_declarator& item)
{
}

void
semantic_analyzer::convert(const direct_declarator::array_part&)
{
}

void
semantic_analyzer::convert(const direct_declarator::function_part& item)
{
}

void
semantic_analyzer::convert(const elaborated_type_specifier& item)
{
	const boost::optional<const class_key&> a_class_key = item.get_class_key();
	const boost::optional<const identifier&> an_identifier = item.get_identifier();

	if(a_class_key && an_identifier)
	{
		scope_cursor_.add_to_current_scope(class_(an_identifier->get_value()));
	}
}

void
semantic_analyzer::convert(const function_definition& item)
{
	/*
	const boost::optional<const declarator_id&> a_declarator_id = item.get_declarator().get_direct_declarator().get_declarator_id();
	if(a_declarator_id)
	{
		const id_expression* const an_id_expression = boost::get<id_expression>(&*a_declarator_id);
		if(an_id_expression)
		{
			const unqualified_id* const an_unqualified_id = boost::get<unqualified_id>(&*an_id_expression);
			if(an_unqualified_id)
			{
				const identifier* const an_identifier = boost::get<identifier>(&*an_unqualified_id);
				if(an_identifier)
				{
					const std::string& function_name = an_identifier->get_value();
					scope_cursor_.add_to_current_scope(function(function_name));
				}
			}
		}
	}
	*/
}

void
semantic_analyzer::convert(const identifier& item)
{
}

void
semantic_analyzer::convert(const init_declarator& item)
{
}

void
semantic_analyzer::convert(const mem_initializer& item)
{
}

void
semantic_analyzer::convert(const member_declaration_function_definition& item)
{
}

void
semantic_analyzer::convert(const member_declaration_member_declarator_list& item)
{
}

void
semantic_analyzer::convert(const member_declaration_unqualified_id& item)
{
}

void
semantic_analyzer::convert(const member_declarator_bit_field_member& item)
{
}

void
semantic_analyzer::convert(const member_declarator_declarator& item)
{
}

void
semantic_analyzer::convert(const member_specification& item)
{
}

void
semantic_analyzer::convert(const member_specification_access_specifier& item)
{
}

void
semantic_analyzer::convert(const namespace_definition& item)
{
	std::string namespace_name;
	const boost::optional<const identifier&> an_identifier = item.get_identifier();
	if(an_identifier)
	{
		namespace_name = an_identifier->get_value();
	}
	scope_cursor_.add_to_current_scope(namespace_(namespace_name));

	const boost::optional<const declaration_seq&> a_declaration_seq = item.get_declaration_seq();
	if(a_declaration_seq)
	{
		scope_cursor_.enter_last_added_scope();
		convert(*a_declaration_seq);
		scope_cursor_.leave_scope();
	}
}

void
semantic_analyzer::convert(const nested_identifier_or_template_id& item)
{
}

void
semantic_analyzer::convert(const nested_name_specifier& item)
{
}

void
semantic_analyzer::convert(const nested_name_specifier::second_part&)
{
}

void
semantic_analyzer::convert(const operator_function_id&)
{
}

void
semantic_analyzer::convert(const parameter_declaration& item)
{
}

void
semantic_analyzer::convert(const parameter_declaration_clause& item)
{
}

void
semantic_analyzer::convert(const ptr_operator& item)
{
}

void
semantic_analyzer::convert(const qualified_identifier& item)
{
}

void
semantic_analyzer::convert(const qualified_nested_id& item)
{
}

void
semantic_analyzer::convert(const qualified_operator_function_id&)
{
}

void
semantic_analyzer::convert(const qualified_template_id& item)
{
}

void
semantic_analyzer::convert(const simple_declaration& item)
{
	const boost::optional<const decl_specifier_seq&> a_decl_specifier_seq = item.get_decl_specifier_seq();
	const boost::optional<const init_declarator_list&> an_optional_init_declarator_list = item.get_init_declarator_list();

	if(an_optional_init_declarator_list)
	{
		const init_declarator_list& an_init_declarator_list = *an_optional_init_declarator_list;
		for(auto i = an_init_declarator_list.begin(); i != an_init_declarator_list.end(); ++i)
		{
			const declarator& a_declarator = i->get_declarator();
			const direct_declarator& a_direct_declarator = a_declarator.get_direct_declarator();

			//get the item name
			std::string name;
			const boost::optional<const declarator_id&> an_optional_declarator_id = a_direct_declarator.get_declarator_id();
			if(an_optional_declarator_id)
			{
				const declarator_id& a_declarator_id = *an_optional_declarator_id;
				if(const id_expression* an_id_expression = boost::get<id_expression>(&a_declarator_id))
				{
					if(const unqualified_id* an_unqualified_id = boost::get<unqualified_id>(an_id_expression))
					{
						if(const identifier* an_identifier = boost::get<identifier>(an_unqualified_id))
						{
							name = an_identifier->get_value();
						}
					}
				}
			}

			//create the appropriate semantic graph node and add it to the current scope
			bool is_item_a_function = false;
			auto a_direct_declarator_other_parts = a_direct_declarator.get_other_parts();
			for(auto j = a_direct_declarator_other_parts.begin(); j != a_direct_declarator_other_parts.end(); ++j)
			{
				direct_declarator::other_part other_part = *j;

				if(direct_declarator::function_part* function_part = boost::get<direct_declarator::function_part>(&other_part))
				{
					//item is a function declaration!
					is_item_a_function = true;

					if(!name.empty())
						scope_cursor_.add_to_current_scope(function(name));
				}
			}
			if(!is_item_a_function)
			{
				//item is a variable declaration!
				if(!name.empty())
					scope_cursor_.add_to_current_scope(variable(name));
			}

		}
	}
}

void
semantic_analyzer::convert(const simple_template_type_specifier& item)
{
}

void
semantic_analyzer::convert(const template_declaration& item)
{
}

void
semantic_analyzer::convert(const template_id& item)
{
}

void
semantic_analyzer::convert(const using_declaration& item)
{
}

void
semantic_analyzer::convert(const using_directive& item)
{
}

void
semantic_analyzer::convert_separator(const std::string& separator)
{
}

}} //namespace socoa::cpp

