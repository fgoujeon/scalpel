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
#include "name_lookup.hpp"

namespace socoa { namespace cpp
{

using namespace syntax_nodes;
using namespace semantic_nodes;

semantic_analyzer::semantic_analyzer():
	conversion_helper_(*this)
{
}

semantic_graph
semantic_analyzer::operator()(const syntax_tree& tree)
{
	//create global namespace
	semantic_graph global_namespace;

	//current scope = global namespace
	scope_cursor_.initialize(global_namespace);

	for
	(
		auto i = tree.begin();
		i != tree.end();
		++i
	)
	{
		convert(i->main_node());
	}

	return global_namespace;
}

void
semantic_analyzer::convert(const class_head&)
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
semantic_analyzer::convert(const ctor_initializer&)
{
}

void
semantic_analyzer::convert(const cv_qualifier&)
{
}

void
semantic_analyzer::convert(const declarator&)
{
}

void
semantic_analyzer::convert(const destructor_name&)
{
}

void
semantic_analyzer::convert(const direct_declarator&)
{
}

void
semantic_analyzer::convert(const direct_declarator::array_part&)
{
}

void
semantic_analyzer::convert(const direct_declarator::function_part&)
{
}

void
semantic_analyzer::convert(const elaborated_type_specifier&)
{
}

void
semantic_analyzer::convert(const function_definition& item)
{
	//get the name and the enclosing scope of the function
	std::string name;
	scope* enclosing_scope = 0;
	const boost::optional<const declarator_id&> a_declarator_id = item.get_declarator().get_direct_declarator().get_declarator_id();
	if(a_declarator_id)
	{
		boost::optional<const id_expression&> an_id_expression = get<id_expression>(a_declarator_id);
		if(an_id_expression)
		{
			boost::optional<const unqualified_id&> an_unqualified_id = get<unqualified_id>(an_id_expression);
			boost::optional<const qualified_id&> a_qualified_id = get<qualified_id>(an_id_expression);

			if(an_unqualified_id)
			{
				boost::optional<const identifier&> an_identifier = get<identifier>(an_unqualified_id);
				if(an_identifier)
				{
					name = an_identifier->get_value();
				}

				enclosing_scope = &scope_cursor_.get_current_scope();
			}
			else if(a_qualified_id)
			{
			//	const qualified_identifier* const a_qualified_identifier =
			//		boost::get<qualified_identifier>(a_qualified_id)
			//	;
				boost::optional<const qualified_nested_id&> a_qualified_nested_id = get<qualified_nested_id>(a_qualified_id);
			//	const qualified_operator_function_id* const a_qualified_operator_function_id =
			//	   	boost::get<qualified_operator_function_id>(a_qualified_id)
			//	;
			//	const qualified_template_id* const a_qualified_template_id =
			//	   	boost::get<qualified_template_id>(a_qualified_id)
			//	;

				if(a_qualified_nested_id)
				{
					bool leading_double_colon = a_qualified_nested_id->has_leading_double_colon();
					const nested_name_specifier& a_nested_name_specifier = a_qualified_nested_id->get_nested_name_specifier();

					if(leading_double_colon)
					{
						enclosing_scope = name_lookup::find_scope(scope_cursor_.get_global_scope(), a_nested_name_specifier);
					}
					else
					{
						enclosing_scope = name_lookup::find_scope(scope_cursor_.get_current_scope(), a_nested_name_specifier);
					}
				}
			}
			else
			{
				assert(false);
			}


		}
	}

	//check whether the function has already been declared
	bool already_declared = false;
	if(!name.empty() && enclosing_scope)
	{
		auto entities = enclosing_scope->named_entities();
		for(auto i = entities.begin(); i != entities.end(); ++i)
		{
			const named_entity& entity = *i;
			///\todo check function signature
			if(entity.name() == name)
			{
				already_declared = true;
				break;
			}
		}
	}

	//if the function hasn't been declared, this definition serves as a declaration
	if(!already_declared && enclosing_scope && !name.empty())
	{
		scope_cursor_.add_to_current_scope(function(name));
	}
}

void
semantic_analyzer::convert(const identifier&)
{
}

void
semantic_analyzer::convert(const init_declarator&)
{
}

void
semantic_analyzer::convert(const mem_initializer&)
{
}

void
semantic_analyzer::convert(const member_declaration_function_definition&)
{
}

void
semantic_analyzer::convert(const member_declaration_member_declarator_list&)
{
}

void
semantic_analyzer::convert(const member_declaration_unqualified_id&)
{
}

void
semantic_analyzer::convert(const member_declarator_bit_field_member&)
{
}

void
semantic_analyzer::convert(const member_declarator_declarator&)
{
}

void
semantic_analyzer::convert(const member_specification&)
{
}

void
semantic_analyzer::convert(const member_specification_access_specifier&)
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
semantic_analyzer::convert(const nested_identifier_or_template_id&)
{
}

void
semantic_analyzer::convert(const nested_name_specifier&)
{
}

void
semantic_analyzer::convert(const nested_name_specifier::next_part&)
{
}

void
semantic_analyzer::convert(const operator_function_id&)
{
}

void
semantic_analyzer::convert(const parameter_declaration&)
{
}

void
semantic_analyzer::convert(const parameter_declaration_clause&)
{
}

void
semantic_analyzer::convert(const ptr_operator&)
{
}

void
semantic_analyzer::convert(const qualified_identifier&)
{
}

void
semantic_analyzer::convert(const qualified_nested_id&)
{
}

void
semantic_analyzer::convert(const qualified_operator_function_id&)
{
}

void
semantic_analyzer::convert(const qualified_template_id&)
{
}

void
semantic_analyzer::convert(const simple_declaration& item)
{
	std::string name;
	bool is_a_class_declaration = false;
	bool is_a_class_forward_declaration = false;
	bool is_a_function_declaration = false;

	const boost::optional<const decl_specifier_seq&> an_optional_decl_specifier_seq = item.get_decl_specifier_seq();
	const boost::optional<const init_declarator_list&> an_optional_init_declarator_list = item.get_init_declarator_list();

	if(an_optional_decl_specifier_seq)
	{
		const decl_specifier_seq& a_decl_specifier_seq = *an_optional_decl_specifier_seq;
		for(auto i = a_decl_specifier_seq.begin(); i != a_decl_specifier_seq.end(); ++i)
		{
			const decl_specifier& a_decl_specifier = i->main_node();

			if(auto a_type_specifier_ptr = get<type_specifier>(&a_decl_specifier))
			{
				if(get<class_specifier>(a_type_specifier_ptr))
				{
					is_a_class_declaration = true;
				}
				else if(auto an_elaborated_type_specifier_ptr = get<elaborated_type_specifier>(a_type_specifier_ptr))
				{
					if(an_elaborated_type_specifier_ptr->get_class_key())
					{
						is_a_class_forward_declaration = true;
						auto an_optional_identifier = an_elaborated_type_specifier_ptr->get_identifier();
						assert(an_optional_identifier);
						name = an_optional_identifier->get_value();
					}
				}
			}
		}
	}

	if(an_optional_init_declarator_list)
	{
		const init_declarator_list& an_init_declarator_list = *an_optional_init_declarator_list;
		for(auto i = an_init_declarator_list.begin(); i != an_init_declarator_list.end(); ++i)
		{
			const declarator& a_declarator = i->main_node().get_declarator();
			const direct_declarator& a_direct_declarator = a_declarator.get_direct_declarator();

			//get the item name
			const boost::optional<const declarator_id&> an_optional_declarator_id = a_direct_declarator.get_declarator_id();
			if(an_optional_declarator_id)
			{
				const declarator_id& a_declarator_id = *an_optional_declarator_id;
				if(boost::optional<const id_expression&> an_id_expression = get<id_expression>(&a_declarator_id))
				{
					if(boost::optional<const unqualified_id&> an_unqualified_id = get<unqualified_id>(an_id_expression))
					{
						if(boost::optional<const identifier&> an_identifier = get<identifier>(an_unqualified_id))
						{
							assert(name.empty());
							name = an_identifier->get_value();
						}
					}
				}
			}

			//determine the appropriate semantic graph node
			auto a_direct_declarator_next_part_seq = a_direct_declarator.get_next_part_seq();
			if(a_direct_declarator_next_part_seq)
			{
				for(auto j = a_direct_declarator_next_part_seq->begin(); j != a_direct_declarator_next_part_seq->end(); ++j)
				{
					const direct_declarator::next_part& next_part = j->main_node();

					if(get<direct_declarator::function_part>(&next_part))
					{
						//item is a function declaration!
						is_a_function_declaration = true;

						if(!name.empty())
							scope_cursor_.add_to_current_scope(function(name));
					}
				}
			}
		}
	}

	if(is_a_class_declaration || is_a_class_forward_declaration)
	{
		if(!name.empty())
			scope_cursor_.add_to_current_scope(class_(name));
	}
	else if(!is_a_function_declaration && !is_a_class_forward_declaration)
	{
		//item is a variable declaration!
		if(!name.empty())
			scope_cursor_.add_to_current_scope(variable(name));
	}
}

void
semantic_analyzer::convert(const simple_template_type_specifier&)
{
}

void
semantic_analyzer::convert(const template_declaration&)
{
}

void
semantic_analyzer::convert(const template_id&)
{
}

void
semantic_analyzer::convert(const using_declaration&)
{
}

void
semantic_analyzer::convert(const using_directive&)
{
}

void
semantic_analyzer::convert_separator(const std::string&)
{
}

}} //namespace socoa::cpp

